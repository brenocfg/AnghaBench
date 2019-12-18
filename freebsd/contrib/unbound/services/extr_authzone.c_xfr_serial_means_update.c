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
typedef  int /*<<< orphan*/  uint32_t ;
struct auth_xfer {int /*<<< orphan*/  serial; scalar_t__ zone_expired; int /*<<< orphan*/  have_zone; } ;

/* Variables and functions */
 scalar_t__ compare_serial (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
xfr_serial_means_update(struct auth_xfer* xfr, uint32_t serial)
{
	if(!xfr->have_zone)
		return 1; /* no zone, anything is better */
	if(xfr->zone_expired)
		return 1; /* expired, the sent serial is better than expired
			data */
	if(compare_serial(xfr->serial, serial) < 0)
		return 1; /* our serial is smaller than the sent serial,
			the data is newer, fetch it */
	return 0;
}