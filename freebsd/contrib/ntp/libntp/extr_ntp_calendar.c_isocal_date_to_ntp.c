#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct isodate {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  lo; } ;
struct TYPE_4__ {TYPE_1__ d_s; } ;

/* Variables and functions */
 TYPE_2__ isocal_date_to_ntp64 (struct isodate const*) ; 

uint32_t
isocal_date_to_ntp(
	const struct isodate *id
	)
{
	/*
	 * Get lower half of 64-bit NTP timestamp from date/time.
	 */
	return isocal_date_to_ntp64(id).d_s.lo;
}