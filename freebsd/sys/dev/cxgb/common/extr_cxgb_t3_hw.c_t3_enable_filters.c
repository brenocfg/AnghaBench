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
typedef  int /*<<< orphan*/  adapter_t ;

/* Variables and functions */
 int /*<<< orphan*/  A_MC5_DB_CONFIG ; 
 int /*<<< orphan*/  A_TP_GLOBAL_CONFIG ; 
 int /*<<< orphan*/  A_TP_INGRESS_CONFIG ; 
 int /*<<< orphan*/  A_TP_IN_CONFIG ; 
 int /*<<< orphan*/  F_FILTEREN ; 
 int /*<<< orphan*/  F_LOOKUPEVERYPKT ; 
 int /*<<< orphan*/  F_NICMODE ; 
 int /*<<< orphan*/  V_FIVETUPLELOOKUP (int) ; 
 int /*<<< orphan*/  t3_set_reg_field (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tp_wr_bits_indirect (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void t3_enable_filters(adapter_t *adap)
{
	t3_set_reg_field(adap, A_TP_IN_CONFIG, F_NICMODE, 0);
	t3_set_reg_field(adap, A_MC5_DB_CONFIG, 0, F_FILTEREN);
	t3_set_reg_field(adap, A_TP_GLOBAL_CONFIG, 0, V_FIVETUPLELOOKUP(3));
	tp_wr_bits_indirect(adap, A_TP_INGRESS_CONFIG, 0, F_LOOKUPEVERYPKT);
}