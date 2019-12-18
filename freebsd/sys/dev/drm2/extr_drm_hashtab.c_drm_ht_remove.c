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
struct drm_open_hash {int /*<<< orphan*/ * table; int /*<<< orphan*/  mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_MEM_HASHTAB ; 
 int /*<<< orphan*/  hashdestroy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void drm_ht_remove(struct drm_open_hash *ht)
{
	if (ht->table) {
		hashdestroy(ht->table, DRM_MEM_HASHTAB, ht->mask);
		ht->table = NULL;
	}
}