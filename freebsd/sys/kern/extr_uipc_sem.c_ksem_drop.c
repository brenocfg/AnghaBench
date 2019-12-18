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
struct ksem {int /*<<< orphan*/  ks_cv; int /*<<< orphan*/  ks_ref; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_KSEM ; 
 int /*<<< orphan*/  cv_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct ksem*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ksem_count_lock ; 
 int /*<<< orphan*/  mac_posixsem_destroy (struct ksem*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsems ; 
 scalar_t__ refcount_release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ksem_drop(struct ksem *ks)
{

	if (refcount_release(&ks->ks_ref)) {
#ifdef MAC
		mac_posixsem_destroy(ks);
#endif
		cv_destroy(&ks->ks_cv);
		free(ks, M_KSEM);
		mtx_lock(&ksem_count_lock);
		nsems--;
		mtx_unlock(&ksem_count_lock);
	}
}