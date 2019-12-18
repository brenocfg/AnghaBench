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
struct hisi_acc_hw_sgl {int /*<<< orphan*/  entry_sum_in_sgl; } ;

/* Variables and functions */

__attribute__((used)) static void inc_hw_sgl_sge(struct hisi_acc_hw_sgl *hw_sgl)
{
	hw_sgl->entry_sum_in_sgl++;
}