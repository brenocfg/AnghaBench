#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vm_prot_t ;
typedef  int /*<<< orphan*/  u_long ;
struct mips_iter {int dummy; } ;
typedef  int /*<<< orphan*/  kvm_walk_pages_cb_t ;
struct TYPE_6__ {scalar_t__* e_ident; } ;
struct TYPE_7__ {TYPE_1__ nlehdr; } ;
typedef  TYPE_2__ kvm_t ;

/* Variables and functions */
 size_t EI_CLASS ; 
 scalar_t__ ELFCLASS64 ; 
 int /*<<< orphan*/  MIPS_PAGE_SIZE ; 
 int /*<<< orphan*/  _kvm_visit_cb (TYPE_2__*,int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _mips_iterator_init (struct mips_iter*,TYPE_2__*) ; 
 scalar_t__ _mips_iterator_next (struct mips_iter*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
_mips_minidump_walk_pages(kvm_t *kd, kvm_walk_pages_cb_t *cb, void *arg)
{
	struct mips_iter it;
	u_long dva, pa, va;
	vm_prot_t prot;

	/* Generate direct mapped entries; need page entries for prot etc? */
	if (kd->nlehdr.e_ident[EI_CLASS] == ELFCLASS64) {
		/* MIPS_XKPHYS_START..MIPS_XKPHYS_END */
		/* MIPS64_KSEG0_START..MIPS64_KSEG0_END */
		/* MIPS64_KSEG1_START..MIPS64_KSEG1_START */
	} else {
		/* MIPS32_KSEG0_START..MIPS32_KSEG0_END */
		/* MIPS32_KSEG1_START..MIPS32_KSEG1_END */
	}

	_mips_iterator_init(&it, kd);
	while (_mips_iterator_next(&it, &pa, &va, &dva, &prot)) {
		if (!_kvm_visit_cb(kd, cb, arg, pa, va, dva,
		    prot, MIPS_PAGE_SIZE, 0)) {
			return (0);
		}
	}
	return (1);
}