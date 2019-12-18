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
typedef  int u32 ;

/* Variables and functions */
 scalar_t__ DCRN_L2C0_ADDR ; 
 scalar_t__ DCRN_L2C0_CMD ; 
 scalar_t__ DCRN_L2C0_DATA ; 
 scalar_t__ DCRN_L2C0_SR ; 
 int L2C_CMD_DIAG ; 
 int L2C_SR_CC ; 
 scalar_t__ dcrbase_l2c ; 
 int mfdcr (scalar_t__) ; 
 int /*<<< orphan*/  mtdcr (scalar_t__,int) ; 

__attribute__((used)) static inline u32 l2c_diag(u32 addr)
{
	mtdcr(dcrbase_l2c + DCRN_L2C0_ADDR, addr);
	mtdcr(dcrbase_l2c + DCRN_L2C0_CMD, L2C_CMD_DIAG);
	while (!(mfdcr(dcrbase_l2c + DCRN_L2C0_SR) & L2C_SR_CC))
		;

	return mfdcr(dcrbase_l2c + DCRN_L2C0_DATA);
}