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
struct ifconfig_lagg_status {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct ifconfig_lagg_status*) ; 

void
ifconfig_lagg_free_lagg_status(struct ifconfig_lagg_status *laggstat)
{
	free(laggstat);
}