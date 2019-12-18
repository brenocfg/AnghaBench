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
struct sscop_param {int timer_cc; int timer_poll; int timer_keep_alive; int timer_no_response; int timer_idle; int maxk; int maxj; int maxcc; int maxpd; } ;

/* Variables and functions */
 int SSCOP_SET_MAXCC ; 
 int SSCOP_SET_MAXJ ; 
 int SSCOP_SET_MAXK ; 
 int SSCOP_SET_MAXPD ; 
 int SSCOP_SET_TCC ; 
 int SSCOP_SET_TIDLE ; 
 int SSCOP_SET_TKA ; 
 int SSCOP_SET_TNR ; 
 int SSCOP_SET_TPOLL ; 
 int /*<<< orphan*/  memset (struct sscop_param*,int /*<<< orphan*/ ,int) ; 

u_int
sscfu_getdefparam(struct sscop_param *p)
{
	memset(p, 0, sizeof(*p));

	p->timer_cc = 1000;
	p->timer_poll = 750;
	p->timer_keep_alive = 2000;
	p->timer_no_response = 7000;
	p->timer_idle = 15000;
	p->maxk = 4096;
	p->maxj = 4096;
	p->maxcc = 4;
	p->maxpd = 25;

	return (SSCOP_SET_TCC | SSCOP_SET_TPOLL | SSCOP_SET_TKA |
	    SSCOP_SET_TNR | SSCOP_SET_TIDLE | SSCOP_SET_MAXK |
	    SSCOP_SET_MAXJ | SSCOP_SET_MAXCC | SSCOP_SET_MAXPD);
}