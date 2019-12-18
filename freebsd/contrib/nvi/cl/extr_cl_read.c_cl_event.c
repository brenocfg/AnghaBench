#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int32_t ;
struct timeval {int tv_sec; int tv_usec; } ;
struct TYPE_8__ {int ibuf; int skip; int /*<<< orphan*/  cw; } ;
struct TYPE_7__ {size_t e_len; void* e_event; int /*<<< orphan*/ * e_csp; } ;
typedef  int /*<<< orphan*/  SCR ;
typedef  TYPE_1__ EVENT ;
typedef  TYPE_2__ CL_PRIVATE ;
typedef  int /*<<< orphan*/  CHAR_T ;

/* Variables and functions */
 TYPE_2__* CLP (int /*<<< orphan*/ *) ; 
 int CL_SIGHUP ; 
 int CL_SIGINT ; 
 int CL_SIGTERM ; 
 int CL_SIGWINCH ; 
 int EC_INTERRUPT ; 
 int EC_QUOTED ; 
 int EC_RAW ; 
 void* E_EOF ; 
 void* E_ERR ; 
 void* E_INTERRUPT ; 
 void* E_SIGHUP ; 
 void* E_SIGTERM ; 
 void* E_STRING ; 
 void* E_TIMEOUT ; 
 void* E_WRESIZE ; 
 int /*<<< orphan*/  F_CLR (TYPE_2__*,int) ; 
 scalar_t__ F_ISSET (TYPE_2__*,int) ; 
 int INPUT2INT5 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,size_t) ; 
#define  INP_EOF 132 
#define  INP_ERR 131 
#define  INP_INTR 130 
#define  INP_OK 129 
#define  INP_TIMEOUT 128 
 scalar_t__ LF_ISSET (int) ; 
 int /*<<< orphan*/  M_ERR ; 
 int SIZE (int) ; 
 int /*<<< orphan*/  abort () ; 
 int cl_read (int /*<<< orphan*/ *,scalar_t__,int,int,int*,struct timeval*) ; 
 int /*<<< orphan*/  cl_resize (int /*<<< orphan*/ *,size_t,size_t) ; 
 scalar_t__ cl_ssize (int /*<<< orphan*/ *,int,size_t*,size_t*,int*) ; 
 int /*<<< orphan*/  memmove (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msgq (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 

int
cl_event(SCR *sp, EVENT *evp, u_int32_t flags, int ms)
{
	struct timeval t, *tp;
	CL_PRIVATE *clp;
	size_t lines, columns;
	int changed, nr = 0;
	CHAR_T *wp;
	size_t wlen;
	int rc;

	/*
	 * Queue signal based events.  We never clear SIGHUP or SIGTERM events,
	 * so that we just keep returning them until the editor dies.
	 */
	clp = CLP(sp);
retest:	if (LF_ISSET(EC_INTERRUPT) || F_ISSET(clp, CL_SIGINT)) {
		if (F_ISSET(clp, CL_SIGINT)) {
			F_CLR(clp, CL_SIGINT);
			evp->e_event = E_INTERRUPT;
		} else
			evp->e_event = E_TIMEOUT;
		return (0);
	}
	if (F_ISSET(clp, CL_SIGHUP | CL_SIGTERM | CL_SIGWINCH)) {
		if (F_ISSET(clp, CL_SIGHUP)) {
			evp->e_event = E_SIGHUP;
			return (0);
		}
		if (F_ISSET(clp, CL_SIGTERM)) {
			evp->e_event = E_SIGTERM;
			return (0);
		}
		if (F_ISSET(clp, CL_SIGWINCH)) {
			F_CLR(clp, CL_SIGWINCH);
			if (cl_ssize(sp, 1, &lines, &columns, &changed))
				return (1);
			if (changed) {
				(void)cl_resize(sp, lines, columns);
				evp->e_event = E_WRESIZE;
				return (0);
			}
			/* No real change, ignore the signal. */
		}
	}

	/* Set timer. */
	if (ms == 0)
		tp = NULL;
	else {
		t.tv_sec = ms / 1000;
		t.tv_usec = (ms % 1000) * 1000;
		tp = &t;
	}

	/* Read input characters. */
read:
	switch (cl_read(sp, LF_ISSET(EC_QUOTED | EC_RAW),
	    clp->ibuf + clp->skip, SIZE(clp->ibuf) - clp->skip, &nr, tp)) {
	case INP_OK:
		rc = INPUT2INT5(sp, clp->cw, clp->ibuf, nr + clp->skip, 
				wp, wlen);
		evp->e_csp = wp;
		evp->e_len = wlen;
		evp->e_event = E_STRING;
		if (rc < 0) {
		    int n = -rc;
		    memmove(clp->ibuf, clp->ibuf + nr + clp->skip - n, n);
		    clp->skip = n;
		    if (wlen == 0)
			goto read;
		} else if (rc == 0)
		    clp->skip = 0;
		else
		    msgq(sp, M_ERR, "323|Invalid input. Truncated.");
		break;
	case INP_EOF:
		evp->e_event = E_EOF;
		break;
	case INP_ERR:
		evp->e_event = E_ERR;
		break;
	case INP_INTR:
		goto retest;
	case INP_TIMEOUT:
		evp->e_event = E_TIMEOUT;
		break;
	default:
		abort();
	}
	return (0);
}