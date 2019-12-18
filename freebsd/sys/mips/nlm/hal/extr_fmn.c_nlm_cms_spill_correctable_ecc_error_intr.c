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
 int /*<<< orphan*/  CMS_MSG_CONFIG ; 
 int nlm_read_cms_reg (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlm_write_cms_reg (int,int /*<<< orphan*/ ,int) ; 

void nlm_cms_spill_correctable_ecc_error_intr(uint64_t base, int en)
{
	uint64_t val;

	val = nlm_read_cms_reg(base, CMS_MSG_CONFIG);
	val |= (en<<4) | (en<<2);
	nlm_write_cms_reg(base, CMS_MSG_CONFIG, val);
}