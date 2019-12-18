#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int ptesize; } ;
struct vmstate {int pte_size; TYPE_1__ hdr; } ;
struct mips_iter {int nptes; scalar_t__ pteindex; TYPE_2__* kd; } ;
typedef  int /*<<< orphan*/  mips64_pte_t ;
typedef  int /*<<< orphan*/  mips32_pte_t ;
struct TYPE_5__ {struct vmstate* vmst; } ;
typedef  TYPE_2__ kvm_t ;

/* Variables and functions */

__attribute__((used)) static void
_mips_iterator_init(struct mips_iter *it, kvm_t *kd)
{
	struct vmstate *vm = kd->vmst;

	it->kd = kd;
	it->pteindex = 0;
	if (vm->pte_size == 64)
		it->nptes = vm->hdr.ptesize / sizeof(mips64_pte_t);
	else
		it->nptes = vm->hdr.ptesize / sizeof(mips32_pte_t);
	return;
}