#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u_int ;
struct sscop_param {int mr; int timer_cc; int timer_poll; int timer_keep_alive; int timer_no_response; int timer_idle; int maxj; int maxk; int maxcc; int maxpd; int maxstat; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  SSCOP_POLLREX ; 
 int /*<<< orphan*/  SSCOP_ROBUST ; 
 int SSCOP_SET_MAXCC ; 
 int SSCOP_SET_MAXJ ; 
 int SSCOP_SET_MAXK ; 
 int SSCOP_SET_MAXPD ; 
 int SSCOP_SET_MAXSTAT ; 
 int SSCOP_SET_MR ; 
 int SSCOP_SET_POLLREX ; 
 int SSCOP_SET_ROBUST ; 
 int SSCOP_SET_TCC ; 
 int SSCOP_SET_TIDLE ; 
 int SSCOP_SET_TKA ; 
 int SSCOP_SET_TNR ; 
 int SSCOP_SET_TPOLL ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  errx (int,char*,...) ; 
 char* optarg ; 
 char* strchr (char*,char) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int strtoul (char*,char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  verb (char*) ; 

void
parse_param(struct sscop_param *param, u_int *pmask, int opt, char *arg)
{
	u_int val;
	char *end, *p;

	if(opt == 'b') {
		param->flags |= SSCOP_ROBUST;
		*pmask |= SSCOP_SET_ROBUST;
		return;
	}
	if(opt == 'x') {
		param->flags |= SSCOP_POLLREX;
		*pmask |= SSCOP_SET_POLLREX;
		return;
	}
	if(opt == 'W') {
		val = (u_int)strtoul(optarg, &end, 0);

		if(*end != '\0')
			errx(1, "bad number to -W '%s'", optarg);
		if(val >= (1 << 24) - 1)
			errx(1, "window too large: 0x%x", val);
		param->mr = val;
		*pmask |= SSCOP_SET_MR;
		return;
	}

	if((p = strchr(arg, '=')) == NULL)
		errx(1, "need '=' in argument to -%c", opt);
	*p++ = 0;
	if(*p == 0)
		errx(1, "argument to -%c %s empty", opt, arg);
	val = strtoul(p, &end, 0);
	if(*end != 0)
		errx(1, "bad number in -%c %s=%s", opt, arg, p);

	if(opt == 't') {
		if(strcmp(arg, "cc") == 0) {
			param->timer_cc = val;
			*pmask |= SSCOP_SET_TCC;
		} else if(strcmp(arg, "poll") == 0) {
			param->timer_poll = val;
			*pmask |= SSCOP_SET_TPOLL;
		} else if(strcmp(arg, "ka") == 0) {
			param->timer_keep_alive = val;
			*pmask |= SSCOP_SET_TKA;
		} else if(strcmp(arg, "nr") == 0) {
			param->timer_no_response = val;
			*pmask |= SSCOP_SET_TNR;
		} else if(strcmp(arg, "idle") == 0) {
			param->timer_idle = val;
			*pmask |= SSCOP_SET_TIDLE;
		} else
			errx(1, "bad timer name '%s'", arg);
		return;
	}

	if(opt == 'a') {
		if(strcmp(arg, "j") == 0) {
			param->maxj = val;
			*pmask |= SSCOP_SET_MAXJ;
		} else if(strcmp(arg, "k") == 0) {
			param->maxk = val;
			*pmask |= SSCOP_SET_MAXK;
		} else if(strcmp(arg, "cc") == 0) {
			param->maxcc = val;
			*pmask |= SSCOP_SET_MAXCC;
		} else if(strcmp(arg, "pd") == 0) {
			param->maxpd = val;
			*pmask |= SSCOP_SET_MAXPD;
		} else if(strcmp(arg, "stat") == 0) {
			param->maxstat = val;
			*pmask |= SSCOP_SET_MAXSTAT;
		} else
			errx(1, "bad parameter '%s'", arg);
		return;
	}

	verb("bad flag");
	abort();
}