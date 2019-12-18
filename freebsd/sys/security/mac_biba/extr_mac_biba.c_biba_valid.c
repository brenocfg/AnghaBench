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
struct TYPE_5__ {int mbe_type; int /*<<< orphan*/  mbe_compartments; int /*<<< orphan*/  mbe_grade; } ;
struct TYPE_6__ {int mbe_type; int /*<<< orphan*/  mbe_compartments; int /*<<< orphan*/  mbe_grade; } ;
struct TYPE_4__ {int mbe_type; int /*<<< orphan*/  mbe_compartments; int /*<<< orphan*/  mbe_grade; } ;
struct mac_biba {int mb_flags; TYPE_2__ mb_rangehigh; TYPE_3__ mb_rangelow; TYPE_1__ mb_effective; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MAC_BIBA_BIT_SET_EMPTY (int /*<<< orphan*/ ) ; 
 int MAC_BIBA_FLAG_EFFECTIVE ; 
 int MAC_BIBA_FLAG_RANGE ; 
#define  MAC_BIBA_TYPE_EQUAL 131 
#define  MAC_BIBA_TYPE_GRADE 130 
#define  MAC_BIBA_TYPE_HIGH 129 
#define  MAC_BIBA_TYPE_LOW 128 
 int MAC_BIBA_TYPE_UNDEF ; 
 int /*<<< orphan*/  biba_dominate_element (TYPE_2__*,TYPE_3__*) ; 

__attribute__((used)) static int
biba_valid(struct mac_biba *mb)
{

	if (mb->mb_flags & MAC_BIBA_FLAG_EFFECTIVE) {
		switch (mb->mb_effective.mbe_type) {
		case MAC_BIBA_TYPE_GRADE:
			break;

		case MAC_BIBA_TYPE_EQUAL:
		case MAC_BIBA_TYPE_HIGH:
		case MAC_BIBA_TYPE_LOW:
			if (mb->mb_effective.mbe_grade != 0 ||
			    !MAC_BIBA_BIT_SET_EMPTY(
			    mb->mb_effective.mbe_compartments))
				return (EINVAL);
			break;

		default:
			return (EINVAL);
		}
	} else {
		if (mb->mb_effective.mbe_type != MAC_BIBA_TYPE_UNDEF)
			return (EINVAL);
	}

	if (mb->mb_flags & MAC_BIBA_FLAG_RANGE) {
		switch (mb->mb_rangelow.mbe_type) {
		case MAC_BIBA_TYPE_GRADE:
			break;

		case MAC_BIBA_TYPE_EQUAL:
		case MAC_BIBA_TYPE_HIGH:
		case MAC_BIBA_TYPE_LOW:
			if (mb->mb_rangelow.mbe_grade != 0 ||
			    !MAC_BIBA_BIT_SET_EMPTY(
			    mb->mb_rangelow.mbe_compartments))
				return (EINVAL);
			break;

		default:
			return (EINVAL);
		}

		switch (mb->mb_rangehigh.mbe_type) {
		case MAC_BIBA_TYPE_GRADE:
			break;

		case MAC_BIBA_TYPE_EQUAL:
		case MAC_BIBA_TYPE_HIGH:
		case MAC_BIBA_TYPE_LOW:
			if (mb->mb_rangehigh.mbe_grade != 0 ||
			    !MAC_BIBA_BIT_SET_EMPTY(
			    mb->mb_rangehigh.mbe_compartments))
				return (EINVAL);
			break;

		default:
			return (EINVAL);
		}
		if (!biba_dominate_element(&mb->mb_rangehigh,
		    &mb->mb_rangelow))
			return (EINVAL);
	} else {
		if (mb->mb_rangelow.mbe_type != MAC_BIBA_TYPE_UNDEF ||
		    mb->mb_rangehigh.mbe_type != MAC_BIBA_TYPE_UNDEF)
			return (EINVAL);
	}

	return (0);
}