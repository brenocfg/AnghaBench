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
struct TYPE_2__ {size_t narenas; } ;

/* Variables and functions */
#define  MALLCTL_ARENAS_ALL 129 
#define  MALLCTL_ARENAS_DESTROYED 128 
 unsigned int UINT_MAX ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__* ctl_arenas ; 

__attribute__((used)) static unsigned
arenas_i2a_impl(size_t i, bool compat, bool validate) {
	unsigned a;

	switch (i) {
	case MALLCTL_ARENAS_ALL:
		a = 0;
		break;
	case MALLCTL_ARENAS_DESTROYED:
		a = 1;
		break;
	default:
		if (compat && i == ctl_arenas->narenas) {
			/*
			 * Provide deprecated backward compatibility for
			 * accessing the merged stats at index narenas rather
			 * than via MALLCTL_ARENAS_ALL.  This is scheduled for
			 * removal in 6.0.0.
			 */
			a = 0;
		} else if (validate && i >= ctl_arenas->narenas) {
			a = UINT_MAX;
		} else {
			/*
			 * This function should never be called for an index
			 * more than one past the range of indices that have
			 * initialized ctl data.
			 */
			assert(i < ctl_arenas->narenas || (!validate && i ==
			    ctl_arenas->narenas));
			a = (unsigned)i + 2;
		}
		break;
	}

	return a;
}