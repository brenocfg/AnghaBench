#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ssize_t ;
typedef  enum xprt_stat { ____Placeholder_xprt_stat } xprt_stat ;
typedef  void* bool_t ;
struct TYPE_5__ {scalar_t__ x_private; } ;
typedef  TYPE_1__ XDR ;
struct TYPE_6__ {scalar_t__ (* readit ) (int /*<<< orphan*/ ,char*,int) ;char* in_hdrp; int in_hdrlen; int in_header; int in_maxrec; int in_reclen; int recvsize; char* in_base; int in_received; int fbtbc; char* in_boundry; char* in_finger; void* last_frag; void* in_haveheader; int /*<<< orphan*/  tcp_handle; } ;
typedef  TYPE_2__ RECSTREAM ;

/* Variables and functions */
 void* FALSE ; 
 int LAST_FRAG ; 
 void* TRUE ; 
 int XPRT_DIED ; 
 int XPRT_IDLE ; 
 int XPRT_MOREREQS ; 
 int ntohl (int) ; 
 int /*<<< orphan*/  realloc_stream (TYPE_2__*,int) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ stub2 (int /*<<< orphan*/ ,char*,int) ; 

bool_t
__xdrrec_getrec(XDR *xdrs, enum xprt_stat *statp, bool_t expectdata)
{
	RECSTREAM *rstrm = (RECSTREAM *)(xdrs->x_private);
	ssize_t n;
	int fraglen;

	if (!rstrm->in_haveheader) {
		n = rstrm->readit(rstrm->tcp_handle, rstrm->in_hdrp,
		    (int)sizeof (rstrm->in_header) - rstrm->in_hdrlen);
		if (n == 0) {
			*statp = expectdata ? XPRT_DIED : XPRT_IDLE;
			return FALSE;
		}
		if (n < 0) {
			*statp = XPRT_DIED;
			return FALSE;
		}
		rstrm->in_hdrp += n;
		rstrm->in_hdrlen += n;
		if (rstrm->in_hdrlen < sizeof (rstrm->in_header)) {
			*statp = XPRT_MOREREQS;
			return FALSE;
		}
		rstrm->in_header = ntohl(rstrm->in_header);
		fraglen = (int)(rstrm->in_header & ~LAST_FRAG);
		if (fraglen == 0 || fraglen > rstrm->in_maxrec ||
		    (rstrm->in_reclen + fraglen) > rstrm->in_maxrec) {
			*statp = XPRT_DIED;
			return FALSE;
		}
		rstrm->in_reclen += fraglen;
		if (rstrm->in_reclen > rstrm->recvsize)
			realloc_stream(rstrm, rstrm->in_reclen);
		if (rstrm->in_header & LAST_FRAG) {
			rstrm->in_header &= ~LAST_FRAG;
			rstrm->last_frag = TRUE;
		}
		/*
		 * We can only reasonably expect to read once from a
		 * non-blocking stream. Reading the fragment header
		 * may have drained the stream.
		 */
		expectdata = FALSE;
	}

	n =  rstrm->readit(rstrm->tcp_handle,
	    rstrm->in_base + rstrm->in_received,
	    (rstrm->in_reclen - rstrm->in_received));

	if (n < 0) {
		*statp = XPRT_DIED;
		return FALSE;
	}

	if (n == 0) {
		*statp = expectdata ? XPRT_DIED : XPRT_IDLE;
		return FALSE;
	}

	rstrm->in_received += n;

	if (rstrm->in_received == rstrm->in_reclen) {
		rstrm->in_haveheader = FALSE;
		rstrm->in_hdrp = (char *)(void *)&rstrm->in_header;
		rstrm->in_hdrlen = 0;
		if (rstrm->last_frag) {
			rstrm->fbtbc = rstrm->in_reclen;
			rstrm->in_boundry = rstrm->in_base + rstrm->in_reclen;
			rstrm->in_finger = rstrm->in_base;
			rstrm->in_reclen = rstrm->in_received = 0;
			*statp = XPRT_MOREREQS;
			return TRUE;
		}
	}

	*statp = XPRT_MOREREQS;
	return FALSE;
}