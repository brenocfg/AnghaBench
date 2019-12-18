#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_long ;
typedef  int /*<<< orphan*/  sockaddr_u ;
struct TYPE_6__ {int l_ui; } ;
typedef  TYPE_1__ l_fp ;
struct TYPE_7__ {int /*<<< orphan*/ * fp; } ;

/* Variables and functions */
 scalar_t__ MJD_1900 ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  filegen_setup (TYPE_3__*,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,double,double,double,double) ; 
 int /*<<< orphan*/  get_systime (TYPE_1__*) ; 
 TYPE_3__ peerstats ; 
 int /*<<< orphan*/  stats_control ; 
 int /*<<< orphan*/  stoa (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ulfptoa (TYPE_1__*,int) ; 

void
record_peer_stats(
	sockaddr_u *addr,
	int	status,
	double	offset,		/* offset */
	double	delay,		/* delay */
	double	dispersion,	/* dispersion */
	double	jitter		/* jitter */
	)
{
	l_fp	now;
	u_long	day;

	if (!stats_control)
		return;

	get_systime(&now);
	filegen_setup(&peerstats, now.l_ui);
	day = now.l_ui / 86400 + MJD_1900;
	now.l_ui %= 86400;
	if (peerstats.fp != NULL) {
		fprintf(peerstats.fp,
		    "%lu %s %s %x %.9f %.9f %.9f %.9f\n", day,
		    ulfptoa(&now, 3), stoa(addr), status, offset,
		    delay, dispersion, jitter);
		fflush(peerstats.fp);
	}
}