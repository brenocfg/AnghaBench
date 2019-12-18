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
struct iop_adma_desc_slot {struct iop3xx_desc_aau* hw_desc; } ;
struct iop3xx_aau_desc_ctrl {int zero_result_err; scalar_t__ zero_result_en; scalar_t__ tx_complete; } ;
struct iop3xx_desc_aau {struct iop3xx_aau_desc_ctrl desc_ctrl_field; } ;
typedef  enum sum_check_flags { ____Placeholder_sum_check_flags } sum_check_flags ;

/* Variables and functions */
 int SUM_CHECK_P ; 
 int /*<<< orphan*/  iop_paranoia (int) ; 

__attribute__((used)) static inline enum sum_check_flags
iop_desc_get_zero_result(struct iop_adma_desc_slot *desc)
{
	struct iop3xx_desc_aau *hw_desc = desc->hw_desc;
	struct iop3xx_aau_desc_ctrl desc_ctrl = hw_desc->desc_ctrl_field;

	iop_paranoia(!(desc_ctrl.tx_complete && desc_ctrl.zero_result_en));
	return desc_ctrl.zero_result_err << SUM_CHECK_P;
}