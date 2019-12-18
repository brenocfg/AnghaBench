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
struct sparc64_msiq_cookie {scalar_t__ msiqid; struct pci_pbm_info* pbm; } ;
struct pci_pbm_info {int msiq_num; int msi_num; struct sparc64_msiq_cookie* msiq_irq_cookies; void* msi_irq_table; scalar_t__ msiq_first; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct sparc64_msiq_cookie*) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int msi_table_alloc(struct pci_pbm_info *pbm)
{
	int size, i;

	size = pbm->msiq_num * sizeof(struct sparc64_msiq_cookie);
	pbm->msiq_irq_cookies = kzalloc(size, GFP_KERNEL);
	if (!pbm->msiq_irq_cookies)
		return -ENOMEM;

	for (i = 0; i < pbm->msiq_num; i++) {
		struct sparc64_msiq_cookie *p;

		p = &pbm->msiq_irq_cookies[i];
		p->pbm = pbm;
		p->msiqid = pbm->msiq_first + i;
	}

	size = pbm->msi_num * sizeof(unsigned int);
	pbm->msi_irq_table = kzalloc(size, GFP_KERNEL);
	if (!pbm->msi_irq_table) {
		kfree(pbm->msiq_irq_cookies);
		pbm->msiq_irq_cookies = NULL;
		return -ENOMEM;
	}

	return 0;
}