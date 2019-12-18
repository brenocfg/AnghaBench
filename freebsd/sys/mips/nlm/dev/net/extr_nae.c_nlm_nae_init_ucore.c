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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  u_int ;

/* Variables and functions */
 int /*<<< orphan*/  NAE_UCORE_IFACEMASK_CFG ; 
 int /*<<< orphan*/  nlm_write_nae_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ucore_spray_config (int,int /*<<< orphan*/ ,int) ; 

void
nlm_nae_init_ucore(uint64_t nae_base, int if_num, u_int ucore_mask)
{
	uint32_t ucfg;

	ucfg = ucore_spray_config(if_num, ucore_mask, 1); /* 1 : write */
	nlm_write_nae_reg(nae_base, NAE_UCORE_IFACEMASK_CFG, ucfg);
}