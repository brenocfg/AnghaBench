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
typedef  int /*<<< orphan*/  uint64_t ;
struct lacp_port {int /*<<< orphan*/  lp_media; } ;
struct lacp_aggregator {int /*<<< orphan*/  la_nports; int /*<<< orphan*/  la_ports; } ;

/* Variables and functions */
 int /*<<< orphan*/  LACP_DPRINTF (struct lacp_port*) ; 
 struct lacp_port* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ifmedia_baudrate (int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint64_t
lacp_aggregator_bandwidth(struct lacp_aggregator *la)
{
	struct lacp_port *lp;
	uint64_t speed;

	lp = TAILQ_FIRST(&la->la_ports);
	if (lp == NULL) {
		return (0);
	}

	speed = ifmedia_baudrate(lp->lp_media);
	speed *= la->la_nports;
	if (speed == 0) {
		LACP_DPRINTF((lp, "speed 0? media=0x%x nports=%d\n",
		    lp->lp_media, la->la_nports));
	}

	return (speed);
}