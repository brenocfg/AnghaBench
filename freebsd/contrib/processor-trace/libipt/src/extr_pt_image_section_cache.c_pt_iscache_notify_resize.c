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
typedef  int /*<<< orphan*/  uint64_t ;
struct pt_section {int dummy; } ;
struct pt_iscache_lru_entry {int dummy; } ;
struct pt_image_section_cache {int dummy; } ;

/* Variables and functions */
 int pt_iscache_lock (struct pt_image_section_cache*) ; 
 int pt_iscache_lru_free (struct pt_iscache_lru_entry*) ; 
 int pt_iscache_lru_prune (struct pt_image_section_cache*,struct pt_iscache_lru_entry**) ; 
 int pt_iscache_lru_resize (struct pt_image_section_cache*,struct pt_section*,int /*<<< orphan*/ ) ; 
 int pt_iscache_unlock (struct pt_image_section_cache*) ; 

int pt_iscache_notify_resize(struct pt_image_section_cache *iscache,
			     struct pt_section *section, uint64_t memsize)
{
	struct pt_iscache_lru_entry *tail;
	int errcode, status;

	tail = NULL;

	errcode = pt_iscache_lock(iscache);
	if (errcode < 0)
		return errcode;

	status = pt_iscache_lru_resize(iscache, section, memsize);
	if (status > 0)
		status = pt_iscache_lru_prune(iscache, &tail);

	errcode = pt_iscache_unlock(iscache);

	if (errcode < 0 || status < 0)
		return (status < 0) ? status : errcode;

	return pt_iscache_lru_free(tail);
}