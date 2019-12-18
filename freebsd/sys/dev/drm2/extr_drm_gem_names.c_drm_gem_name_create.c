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
typedef  int uint32_t ;
struct drm_gem_names {int /*<<< orphan*/  lock; int /*<<< orphan*/  unr; } ;
struct drm_gem_name {int name; void* ptr; } ;

/* Variables and functions */
 int EALREADY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ ,struct drm_gem_name*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_GEM_NAMES ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int alloc_unr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct drm_gem_name*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gem_name_hash_index (struct drm_gem_names*,int) ; 
 int /*<<< orphan*/  link ; 
 struct drm_gem_name* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

int
drm_gem_name_create(struct drm_gem_names *names, void *p, uint32_t *name)
{
	struct drm_gem_name *np;

	if (*name != 0) {
		return (-EALREADY);
	}

	np = malloc(sizeof(struct drm_gem_name), M_GEM_NAMES, M_WAITOK);
	mtx_lock(&names->lock);
	np->name = alloc_unr(names->unr);
	if (np->name == -1) {
		mtx_unlock(&names->lock);
		free(np, M_GEM_NAMES);
		return (-ENOMEM);
	}
	*name = np->name;
	np->ptr = p;
	LIST_INSERT_HEAD(gem_name_hash_index(names, np->name), np, link);
	mtx_unlock(&names->lock);
	return (0);
}