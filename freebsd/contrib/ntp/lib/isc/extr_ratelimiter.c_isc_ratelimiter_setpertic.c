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
typedef  int isc_uint32_t ;
struct TYPE_3__ {int pertic; } ;
typedef  TYPE_1__ isc_ratelimiter_t ;

/* Variables and functions */

void
isc_ratelimiter_setpertic(isc_ratelimiter_t *rl, isc_uint32_t pertic) {
	if (pertic == 0)
		pertic = 1;
	rl->pertic = pertic;
}