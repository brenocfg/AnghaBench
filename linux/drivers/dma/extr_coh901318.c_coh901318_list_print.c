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
struct coh901318_lli {struct coh901318_lli* virt_link_addr; int /*<<< orphan*/  link_addr; int /*<<< orphan*/  dst_addr; int /*<<< orphan*/  src_addr; int /*<<< orphan*/  control; } ;
struct coh901318_chan {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  COHC_2_DEV (struct coh901318_chan*) ; 
 int /*<<< orphan*/  dev_vdbg (int /*<<< orphan*/ ,char*,int,struct coh901318_lli*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct coh901318_lli*) ; 

__attribute__((used)) static void coh901318_list_print(struct coh901318_chan *cohc,
				 struct coh901318_lli *lli)
{
	struct coh901318_lli *l = lli;
	int i = 0;

	while (l) {
		dev_vdbg(COHC_2_DEV(cohc), "i %d, lli %p, ctrl 0x%x, src %pad"
			 ", dst %pad, link %pad virt_link_addr 0x%p\n",
			 i, l, l->control, &l->src_addr, &l->dst_addr,
			 &l->link_addr, l->virt_link_addr);
		i++;
		l = l->virt_link_addr;
	}
}