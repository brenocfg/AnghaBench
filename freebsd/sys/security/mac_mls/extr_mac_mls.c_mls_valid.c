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
struct TYPE_5__ {int mme_type; int /*<<< orphan*/  mme_compartments; int /*<<< orphan*/  mme_level; } ;
struct TYPE_6__ {int mme_type; int /*<<< orphan*/  mme_compartments; int /*<<< orphan*/  mme_level; } ;
struct TYPE_4__ {int mme_type; int /*<<< orphan*/  mme_compartments; int /*<<< orphan*/  mme_level; } ;
struct mac_mls {int mm_flags; TYPE_2__ mm_rangehigh; TYPE_3__ mm_rangelow; TYPE_1__ mm_effective; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MAC_MLS_BIT_SET_EMPTY (int /*<<< orphan*/ ) ; 
 int MAC_MLS_FLAG_EFFECTIVE ; 
 int MAC_MLS_FLAG_RANGE ; 
#define  MAC_MLS_TYPE_EQUAL 131 
#define  MAC_MLS_TYPE_HIGH 130 
#define  MAC_MLS_TYPE_LEVEL 129 
#define  MAC_MLS_TYPE_LOW 128 
 int MAC_MLS_TYPE_UNDEF ; 
 int /*<<< orphan*/  mls_dominate_element (TYPE_2__*,TYPE_3__*) ; 

__attribute__((used)) static int
mls_valid(struct mac_mls *mm)
{

	if (mm->mm_flags & MAC_MLS_FLAG_EFFECTIVE) {
		switch (mm->mm_effective.mme_type) {
		case MAC_MLS_TYPE_LEVEL:
			break;

		case MAC_MLS_TYPE_EQUAL:
		case MAC_MLS_TYPE_HIGH:
		case MAC_MLS_TYPE_LOW:
			if (mm->mm_effective.mme_level != 0 ||
			    !MAC_MLS_BIT_SET_EMPTY(
			    mm->mm_effective.mme_compartments))
				return (EINVAL);
			break;

		default:
			return (EINVAL);
		}
	} else {
		if (mm->mm_effective.mme_type != MAC_MLS_TYPE_UNDEF)
			return (EINVAL);
	}

	if (mm->mm_flags & MAC_MLS_FLAG_RANGE) {
		switch (mm->mm_rangelow.mme_type) {
		case MAC_MLS_TYPE_LEVEL:
			break;

		case MAC_MLS_TYPE_EQUAL:
		case MAC_MLS_TYPE_HIGH:
		case MAC_MLS_TYPE_LOW:
			if (mm->mm_rangelow.mme_level != 0 ||
			    !MAC_MLS_BIT_SET_EMPTY(
			    mm->mm_rangelow.mme_compartments))
				return (EINVAL);
			break;

		default:
			return (EINVAL);
		}

		switch (mm->mm_rangehigh.mme_type) {
		case MAC_MLS_TYPE_LEVEL:
			break;

		case MAC_MLS_TYPE_EQUAL:
		case MAC_MLS_TYPE_HIGH:
		case MAC_MLS_TYPE_LOW:
			if (mm->mm_rangehigh.mme_level != 0 ||
			    !MAC_MLS_BIT_SET_EMPTY(
			    mm->mm_rangehigh.mme_compartments))
				return (EINVAL);
			break;

		default:
			return (EINVAL);
		}
		if (!mls_dominate_element(&mm->mm_rangehigh,
		    &mm->mm_rangelow))
			return (EINVAL);
	} else {
		if (mm->mm_rangelow.mme_type != MAC_MLS_TYPE_UNDEF ||
		    mm->mm_rangehigh.mme_type != MAC_MLS_TYPE_UNDEF)
			return (EINVAL);
	}

	return (0);
}