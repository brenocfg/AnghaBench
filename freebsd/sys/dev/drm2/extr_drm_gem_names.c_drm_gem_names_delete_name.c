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
struct drm_gem_names {int /*<<< orphan*/  unr; int /*<<< orphan*/  lock; } ;
struct drm_gem_name {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_REMOVE (struct drm_gem_name*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  M_GEM_NAMES ; 
 int /*<<< orphan*/  free (struct drm_gem_name*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_unr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  link ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
drm_gem_names_delete_name(struct drm_gem_names *names, struct drm_gem_name *np)
{

	mtx_assert(&names->lock, MA_OWNED);
	LIST_REMOVE(np, link);
	mtx_unlock(&names->lock);
	free_unr(names->unr, np->name);
	free(np, M_GEM_NAMES);
}