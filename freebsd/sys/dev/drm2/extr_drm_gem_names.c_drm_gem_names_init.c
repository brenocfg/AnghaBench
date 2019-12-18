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
struct drm_gem_names {int /*<<< orphan*/  lock; int /*<<< orphan*/  hash_mask; int /*<<< orphan*/  names_hash; int /*<<< orphan*/  unr; } ;

/* Variables and functions */
 int /*<<< orphan*/  INT_MAX ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  M_GEM_NAMES ; 
 int /*<<< orphan*/  hashinit (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  new_unrhdr (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
drm_gem_names_init(struct drm_gem_names *names)
{

	names->unr = new_unrhdr(1, INT_MAX, NULL); /* XXXKIB */
	names->names_hash = hashinit(1000 /* XXXKIB */, M_GEM_NAMES,
	    &names->hash_mask);
	mtx_init(&names->lock, "drmnames", NULL, MTX_DEF);
}