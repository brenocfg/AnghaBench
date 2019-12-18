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
typedef  unsigned long long uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  CMS_OUTPUTQ_CONFIG (int) ; 
 unsigned long long nlm_read_cms_reg (unsigned long long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlm_write_cms_reg (unsigned long long,int /*<<< orphan*/ ,unsigned long long) ; 

void nlm_cms_outputq_clr_intr(uint64_t base, int qid)
{
	uint64_t val;
	val = nlm_read_cms_reg(base, CMS_OUTPUTQ_CONFIG(qid));
	val |= (1ULL<<59);
	nlm_write_cms_reg(base, CMS_OUTPUTQ_CONFIG(qid), val);
}