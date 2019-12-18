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
 int /*<<< orphan*/  XLP_PCI_DEVINFO_REG0 ; 
 int /*<<< orphan*/  nlm_cms_setup_credits (int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  nlm_get_cms_pcibase (int) ; 
 int /*<<< orphan*/  nlm_get_cms_regbase (int) ; 
 int nlm_read_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
xlp_msgring_cpu_init(int node, int cpu, int credit)
{
	uint64_t cmspcibase = nlm_get_cms_pcibase(node);
	uint64_t cmsbase = nlm_get_cms_regbase(node);
	int qid, maxqid, src;

	maxqid = nlm_read_reg(cmspcibase, XLP_PCI_DEVINFO_REG0);

	/* cpu credit setup is done only from thread-0 of each core */
	if((cpu % 4) == 0) {
		src = cpu << 2; /* each thread has 4 vc's */
		for (qid = 0; qid < maxqid; qid++)
			nlm_cms_setup_credits(cmsbase, qid, src, credit);
	}
}