#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vm_page_t ;
struct mbuf_ext_pgs {int npgs; int /*<<< orphan*/ * pa; } ;
struct TYPE_2__ {struct mbuf_ext_pgs* ext_pgs; } ;
struct mbuf {TYPE_1__ m_ext; } ;

/* Variables and functions */
 int /*<<< orphan*/  MBUF_EXT_PGS_ASSERT (struct mbuf*) ; 
 int /*<<< orphan*/  PHYS_TO_VM_PAGE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_page_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_page_unwire_noq (int /*<<< orphan*/ ) ; 

void
mb_free_mext_pgs(struct mbuf *m)
{
	struct mbuf_ext_pgs *ext_pgs;
	vm_page_t pg;

	MBUF_EXT_PGS_ASSERT(m);
	ext_pgs = m->m_ext.ext_pgs;
	for (int i = 0; i < ext_pgs->npgs; i++) {
		pg = PHYS_TO_VM_PAGE(ext_pgs->pa[i]);
		vm_page_unwire_noq(pg);
		vm_page_free(pg);
	}
}