#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int size; } ;
struct pktcdvd_device {int offset; TYPE_1__ settings; } ;
typedef  int sector_t ;

/* Variables and functions */

__attribute__((used)) static sector_t get_zone(sector_t sector, struct pktcdvd_device *pd)
{
	return (sector + pd->offset) & ~(sector_t)(pd->settings.size - 1);
}