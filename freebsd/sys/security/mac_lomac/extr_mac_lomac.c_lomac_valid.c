#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int mle_type; } ;
struct TYPE_8__ {int mle_type; } ;
struct TYPE_5__ {int mle_type; } ;
struct TYPE_6__ {int mle_type; } ;
struct mac_lomac {int ml_flags; TYPE_3__ ml_rangehigh; TYPE_4__ ml_rangelow; TYPE_1__ ml_auxsingle; TYPE_2__ ml_single; } ;

/* Variables and functions */
 int EINVAL ; 
 int MAC_LOMAC_FLAG_AUX ; 
 int MAC_LOMAC_FLAG_RANGE ; 
 int MAC_LOMAC_FLAG_SINGLE ; 
#define  MAC_LOMAC_TYPE_EQUAL 131 
#define  MAC_LOMAC_TYPE_GRADE 130 
#define  MAC_LOMAC_TYPE_HIGH 129 
#define  MAC_LOMAC_TYPE_LOW 128 
 int MAC_LOMAC_TYPE_UNDEF ; 
 int /*<<< orphan*/  lomac_dominate_element (TYPE_3__*,TYPE_4__*) ; 

__attribute__((used)) static int
lomac_valid(struct mac_lomac *ml)
{

	if (ml->ml_flags & MAC_LOMAC_FLAG_SINGLE) {
		switch (ml->ml_single.mle_type) {
		case MAC_LOMAC_TYPE_GRADE:
		case MAC_LOMAC_TYPE_EQUAL:
		case MAC_LOMAC_TYPE_HIGH:
		case MAC_LOMAC_TYPE_LOW:
			break;

		default:
			return (EINVAL);
		}
	} else {
		if (ml->ml_single.mle_type != MAC_LOMAC_TYPE_UNDEF)
			return (EINVAL);
	}

	if (ml->ml_flags & MAC_LOMAC_FLAG_AUX) {
		switch (ml->ml_auxsingle.mle_type) {
		case MAC_LOMAC_TYPE_GRADE:
		case MAC_LOMAC_TYPE_EQUAL:
		case MAC_LOMAC_TYPE_HIGH:
		case MAC_LOMAC_TYPE_LOW:
			break;

		default:
			return (EINVAL);
		}
	} else {
		if (ml->ml_auxsingle.mle_type != MAC_LOMAC_TYPE_UNDEF)
			return (EINVAL);
	}

	if (ml->ml_flags & MAC_LOMAC_FLAG_RANGE) {
		switch (ml->ml_rangelow.mle_type) {
		case MAC_LOMAC_TYPE_GRADE:
		case MAC_LOMAC_TYPE_EQUAL:
		case MAC_LOMAC_TYPE_HIGH:
		case MAC_LOMAC_TYPE_LOW:
			break;

		default:
			return (EINVAL);
		}

		switch (ml->ml_rangehigh.mle_type) {
		case MAC_LOMAC_TYPE_GRADE:
		case MAC_LOMAC_TYPE_EQUAL:
		case MAC_LOMAC_TYPE_HIGH:
		case MAC_LOMAC_TYPE_LOW:
			break;

		default:
			return (EINVAL);
		}
		if (!lomac_dominate_element(&ml->ml_rangehigh,
		    &ml->ml_rangelow))
			return (EINVAL);
	} else {
		if (ml->ml_rangelow.mle_type != MAC_LOMAC_TYPE_UNDEF ||
		    ml->ml_rangehigh.mle_type != MAC_LOMAC_TYPE_UNDEF)
			return (EINVAL);
	}

	return (0);
}