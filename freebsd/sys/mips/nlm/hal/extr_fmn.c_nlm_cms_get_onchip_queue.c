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

/* Variables and functions */
 int /*<<< orphan*/  CMS_OUTPUTQ_CONFIG (int) ; 
 int /*<<< orphan*/  nlm_read_cms_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

uint64_t nlm_cms_get_onchip_queue (uint64_t base, int qid)
{
	return nlm_read_cms_reg(base, CMS_OUTPUTQ_CONFIG(qid));
}