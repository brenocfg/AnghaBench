#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_long ;
typedef  int /*<<< orphan*/  sockaddr_u ;
struct TYPE_6__ {int l_ui; } ;
typedef  TYPE_1__ l_fp ;
struct TYPE_7__ {int /*<<< orphan*/ * fp; } ;

/* Variables and functions */
 scalar_t__ MJD_1900 ; 
 TYPE_4__ clockstats ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  filegen_setup (TYPE_4__*,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  get_systime (TYPE_1__*) ; 
 int /*<<< orphan*/  stats_control ; 
 int /*<<< orphan*/  stoa (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ulfptoa (TYPE_1__*,int) ; 

void
record_clock_stats(
	sockaddr_u *addr,
	const char *text	/* timecode string */
	)
{
	l_fp	now;
	u_long	day;

	if (!stats_control)
		return;

	get_systime(&now);
	filegen_setup(&clockstats, now.l_ui);
	day = now.l_ui / 86400 + MJD_1900;
	now.l_ui %= 86400;
	if (clockstats.fp != NULL) {
		fprintf(clockstats.fp, "%lu %s %s %s\n", day,
		    ulfptoa(&now, 3), stoa(addr), text);
		fflush(clockstats.fp);
	}
}