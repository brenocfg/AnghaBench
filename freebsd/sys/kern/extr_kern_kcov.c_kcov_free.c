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
typedef  int /*<<< orphan*/  vm_page_t ;
struct kcov_info {scalar_t__ kvaddr; size_t bufsize; int /*<<< orphan*/ * bufobj; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_KCOV_INFO ; 
 size_t PAGE_SIZE ; 
 int /*<<< orphan*/  VM_OBJECT_WLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VM_OBJECT_WUNLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct kcov_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kva_free (scalar_t__,size_t) ; 
 int /*<<< orphan*/  pmap_qremove (scalar_t__,size_t) ; 
 int /*<<< orphan*/  vm_object_deallocate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vm_page_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_page_next (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_page_unwire_noq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
kcov_free(struct kcov_info *info)
{
	vm_page_t m;
	size_t i;

	if (info->kvaddr != 0) {
		pmap_qremove(info->kvaddr, info->bufsize / PAGE_SIZE);
		kva_free(info->kvaddr, info->bufsize);
	}
	if (info->bufobj != NULL) {
		VM_OBJECT_WLOCK(info->bufobj);
		m = vm_page_lookup(info->bufobj, 0);
		for (i = 0; i < info->bufsize / PAGE_SIZE; i++) {
			vm_page_unwire_noq(m);
			m = vm_page_next(m);
		}
		VM_OBJECT_WUNLOCK(info->bufobj);
		vm_object_deallocate(info->bufobj);
	}
	free(info, M_KCOV_INFO);
}