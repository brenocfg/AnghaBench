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
 int /*<<< orphan*/  nlm_cms_per_queue_level_intr (int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  nlm_cms_per_queue_timer_intr (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlm_get_cms_regbase (int) ; 

void
xlp_cms_enable_intr(int node, int cpu, int type, int watermark)
{
	uint64_t cmsbase;
	int i, qid;

	cmsbase = nlm_get_cms_regbase(node);

	for (i = 0; i < 4; i++) {
		qid = (i + (cpu * 4)) & 0x7f;
		nlm_cms_per_queue_level_intr(cmsbase, qid, type, watermark);
		nlm_cms_per_queue_timer_intr(cmsbase, qid, 0x1, 0);
	}
}