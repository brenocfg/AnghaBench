#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  sin; int /*<<< orphan*/  name; int /*<<< orphan*/  ifnum; scalar_t__ ignore_packets; } ;
typedef  TYPE_1__ endpt ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_INFO ; 
 int /*<<< orphan*/  msyslog (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sptoa (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
log_listen_address(
	endpt *	ep
	)
{
	msyslog(LOG_INFO, "%s on %d %s %s",
		(ep->ignore_packets)
		    ? "Listen and drop"
		    : "Listen normally",
		ep->ifnum,
		ep->name,
		sptoa(&ep->sin));
}