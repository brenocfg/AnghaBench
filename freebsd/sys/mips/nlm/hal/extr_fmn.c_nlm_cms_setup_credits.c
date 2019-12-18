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
typedef  int uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  CMS_OUTPUTQ_CREDIT_CFG ; 
 int /*<<< orphan*/  nlm_write_cms_reg (int,int /*<<< orphan*/ ,int) ; 

void nlm_cms_setup_credits(uint64_t base, int destid, int srcid, int credit)
{
	uint64_t val;

	val = (((uint64_t)credit << 24) | (destid << 12) | (srcid << 0));
	nlm_write_cms_reg(base, CMS_OUTPUTQ_CREDIT_CFG, val);

}