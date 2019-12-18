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
struct TYPE_6__ {scalar_t__ mme_type; } ;
struct TYPE_5__ {scalar_t__ mme_type; } ;
struct TYPE_4__ {scalar_t__ mme_type; } ;
struct mac_mls {int mm_flags; TYPE_3__ mm_rangehigh; TYPE_2__ mm_rangelow; TYPE_1__ mm_effective; } ;

/* Variables and functions */
 int MAC_MLS_FLAG_EFFECTIVE ; 
 int MAC_MLS_FLAG_RANGE ; 
 scalar_t__ MAC_MLS_TYPE_EQUAL ; 

__attribute__((used)) static int
mls_contains_equal(struct mac_mls *mm)
{

	if (mm->mm_flags & MAC_MLS_FLAG_EFFECTIVE)
		if (mm->mm_effective.mme_type == MAC_MLS_TYPE_EQUAL)
			return (1);

	if (mm->mm_flags & MAC_MLS_FLAG_RANGE) {
		if (mm->mm_rangelow.mme_type == MAC_MLS_TYPE_EQUAL)
			return (1);
		if (mm->mm_rangehigh.mme_type == MAC_MLS_TYPE_EQUAL)
			return (1);
	}

	return (0);
}