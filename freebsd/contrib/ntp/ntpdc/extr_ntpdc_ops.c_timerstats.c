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
typedef  int /*<<< orphan*/  u_long ;
struct parse {int dummy; } ;
struct info_timer_stats {int /*<<< orphan*/  xmtcalls; int /*<<< orphan*/  overflows; int /*<<< orphan*/  alarms; int /*<<< orphan*/  timereset; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ IMPL_XNTPD ; 
 scalar_t__ IMPL_XNTPD_OLD ; 
 int INFO_ERR_IMPL ; 
 int /*<<< orphan*/  REQ_TIMER_STATS ; 
 int /*<<< orphan*/  check1item (size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  checkitemsize (size_t,int) ; 
 int doquery (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t*,size_t*,void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ impl_ver ; 
 scalar_t__ ntohl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
timerstats(
	struct parse *pcmd,
	FILE *fp
	)
{
	struct info_timer_stats *tim;
	size_t items;
	size_t itemsize;
	int res;

again:
	res = doquery(impl_ver, REQ_TIMER_STATS, 0, 0, 0, NULL, &items,
		      &itemsize, (void *)&tim, 0, sizeof(*tim));
	
	if (res == INFO_ERR_IMPL && impl_ver == IMPL_XNTPD) {
		impl_ver = IMPL_XNTPD_OLD;
		goto again;
	}

	if (res != 0)
		return;

	if (!check1item(items, fp))
		return;

	if (!checkitemsize(itemsize, sizeof(*tim)))
		return;

	fprintf(fp, "time since reset:  %lu\n",
		(u_long)ntohl(tim->timereset));
	fprintf(fp, "alarms handled:    %lu\n",
		(u_long)ntohl(tim->alarms));
	fprintf(fp, "alarm overruns:    %lu\n",
		(u_long)ntohl(tim->overflows));
	fprintf(fp, "calls to transmit: %lu\n",
		(u_long)ntohl(tim->xmtcalls));
}