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
typedef  enum ib_mig_state { ____Placeholder_ib_mig_state } ib_mig_state ;

/* Variables and functions */
 int IB_MIG_ARMED ; 
 int IB_MIG_MIGRATED ; 
 int IB_MIG_REARM ; 

__attribute__((used)) static inline enum ib_mig_state to_ib_mig_state(int mthca_mig_state)
{
	switch (mthca_mig_state) {
	case 0:  return IB_MIG_ARMED;
	case 1:  return IB_MIG_REARM;
	case 3:  return IB_MIG_MIGRATED;
	default: return -1;
	}
}