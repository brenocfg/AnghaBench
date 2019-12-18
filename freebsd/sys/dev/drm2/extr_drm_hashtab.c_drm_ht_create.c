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
struct drm_open_hash {int size; unsigned int order; int /*<<< orphan*/ * table; int /*<<< orphan*/  mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  DRM_MEM_HASHTAB ; 
 int ENOMEM ; 
 int /*<<< orphan*/  HASH_NOWAIT ; 
 int /*<<< orphan*/ * hashinit_flags (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int drm_ht_create(struct drm_open_hash *ht, unsigned int order)
{
	ht->size = 1 << order;
	ht->order = order;
	ht->table = NULL;
	ht->table = hashinit_flags(ht->size, DRM_MEM_HASHTAB, &ht->mask,
	    HASH_NOWAIT);
	if (!ht->table) {
		DRM_ERROR("Out of memory for hash table\n");
		return -ENOMEM;
	}
	return 0;
}