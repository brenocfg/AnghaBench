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
struct drm_gem_names {int hash_mask; int /*<<< orphan*/  unr; int /*<<< orphan*/ * names_hash; int /*<<< orphan*/  lock; } ;
struct drm_gem_name {int dummy; } ;

/* Variables and functions */
 struct drm_gem_name* LIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  M_GEM_NAMES ; 
 int /*<<< orphan*/  delete_unrhdr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_gem_names_delete_name (struct drm_gem_names*,struct drm_gem_name*) ; 
 int /*<<< orphan*/  hashdestroy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

void
drm_gem_names_fini(struct drm_gem_names *names)
{
	struct drm_gem_name *np;
	int i;

	mtx_lock(&names->lock);
	for (i = 0; i <= names->hash_mask; i++) {
		while ((np = LIST_FIRST(&names->names_hash[i])) != NULL) {
			drm_gem_names_delete_name(names, np);
			mtx_lock(&names->lock);
		}
	}
	mtx_unlock(&names->lock);
	mtx_destroy(&names->lock);
	hashdestroy(names->names_hash, M_GEM_NAMES, names->hash_mask);
	delete_unrhdr(names->unr);
}