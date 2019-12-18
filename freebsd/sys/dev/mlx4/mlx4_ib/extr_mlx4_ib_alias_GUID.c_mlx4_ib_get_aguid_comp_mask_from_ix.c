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
typedef  int /*<<< orphan*/  ib_sa_comp_mask ;

/* Variables and functions */
 int /*<<< orphan*/  IB_SA_COMP_MASK (int) ; 

ib_sa_comp_mask mlx4_ib_get_aguid_comp_mask_from_ix(int index)
{
	return IB_SA_COMP_MASK(4 + index);
}