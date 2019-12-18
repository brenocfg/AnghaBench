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
typedef  size_t uint8_t ;

/* Variables and functions */
 size_t DCBX_INVALID_COS ; 
 size_t ELINK_DCBX_MAX_NUM_COS ; 

__attribute__((used)) static void elink_ets_e3b0_sp_pri_to_cos_init(uint8_t *sp_pri_to_cos)
{
	uint8_t pri = 0;
	for (pri = 0; pri < ELINK_DCBX_MAX_NUM_COS; pri++)
		sp_pri_to_cos[pri] = DCBX_INVALID_COS;
}