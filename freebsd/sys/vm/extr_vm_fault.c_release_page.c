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
struct faultstate {int /*<<< orphan*/ * m; } ;

/* Variables and functions */
 int /*<<< orphan*/  vm_page_deactivate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vm_page_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vm_page_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vm_page_xunbusy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void
release_page(struct faultstate *fs)
{

	if (fs->m != NULL) {
		/*
		 * fs->m's object lock might not be held, so the page must be
		 * kept busy until we are done with it.
		 */
		vm_page_lock(fs->m);
		vm_page_deactivate(fs->m);
		vm_page_unlock(fs->m);
		vm_page_xunbusy(fs->m);
		fs->m = NULL;
	}
}