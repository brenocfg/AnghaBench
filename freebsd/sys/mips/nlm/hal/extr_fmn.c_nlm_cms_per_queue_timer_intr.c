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
 int /*<<< orphan*/  CMS_OUTPUTQ_CONFIG (int) ; 
 int nlm_read_cms_reg (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlm_write_cms_reg (int,int /*<<< orphan*/ ,int) ; 

void nlm_cms_per_queue_timer_intr(uint64_t base, int qid, int sub_type,
					int intr_val)
{
	uint64_t val;

	val = nlm_read_cms_reg(base, CMS_OUTPUTQ_CONFIG(qid));

	val &= ~((0x7ULL << 51) | (0x3ULL << 49));

	val |= (((uint64_t)sub_type<<49) |
		((uint64_t)intr_val<<51));

	nlm_write_cms_reg(base, CMS_OUTPUTQ_CONFIG(qid), val);
}