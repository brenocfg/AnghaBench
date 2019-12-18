#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ mbe_type; } ;
struct TYPE_5__ {scalar_t__ mbe_type; } ;
struct TYPE_4__ {scalar_t__ mbe_type; } ;
struct mac_biba {int mb_flags; TYPE_3__ mb_rangehigh; TYPE_2__ mb_rangelow; TYPE_1__ mb_effective; } ;

/* Variables and functions */
 int MAC_BIBA_FLAG_EFFECTIVE ; 
 int MAC_BIBA_FLAG_RANGE ; 
 scalar_t__ MAC_BIBA_TYPE_EQUAL ; 

__attribute__((used)) static int
biba_contains_equal(struct mac_biba *mb)
{

	if (mb->mb_flags & MAC_BIBA_FLAG_EFFECTIVE) {
		if (mb->mb_effective.mbe_type == MAC_BIBA_TYPE_EQUAL)
			return (1);
	}

	if (mb->mb_flags & MAC_BIBA_FLAG_RANGE) {
		if (mb->mb_rangelow.mbe_type == MAC_BIBA_TYPE_EQUAL)
			return (1);
		if (mb->mb_rangehigh.mbe_type == MAC_BIBA_TYPE_EQUAL)
			return (1);
	}

	return (0);
}