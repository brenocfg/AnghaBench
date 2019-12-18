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
#define  MLX5_QP_PM_ARMED 130 
#define  MLX5_QP_PM_MIGRATED 129 
#define  MLX5_QP_PM_REARM 128 

__attribute__((used)) static inline enum ib_mig_state to_ib_mig_state(int mlx5_mig_state)
{
	switch (mlx5_mig_state) {
	case MLX5_QP_PM_ARMED:		return IB_MIG_ARMED;
	case MLX5_QP_PM_REARM:		return IB_MIG_REARM;
	case MLX5_QP_PM_MIGRATED:	return IB_MIG_MIGRATED;
	default: return -1;
	}
}