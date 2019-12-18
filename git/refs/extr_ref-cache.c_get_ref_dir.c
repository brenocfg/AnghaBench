#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ref_dir {TYPE_2__* cache; } ;
struct TYPE_3__ {struct ref_dir subdir; } ;
struct ref_entry {int flag; int /*<<< orphan*/  name; TYPE_1__ u; } ;
struct TYPE_4__ {int /*<<< orphan*/  ref_store; int /*<<< orphan*/  (* fill_ref_dir ) (int /*<<< orphan*/ ,struct ref_dir*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUG (char*) ; 
 int REF_DIR ; 
 int REF_INCOMPLETE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct ref_dir*,int /*<<< orphan*/ ) ; 

struct ref_dir *get_ref_dir(struct ref_entry *entry)
{
	struct ref_dir *dir;
	assert(entry->flag & REF_DIR);
	dir = &entry->u.subdir;
	if (entry->flag & REF_INCOMPLETE) {
		if (!dir->cache->fill_ref_dir)
			BUG("incomplete ref_store without fill_ref_dir function");

		dir->cache->fill_ref_dir(dir->cache->ref_store, dir, entry->name);
		entry->flag &= ~REF_INCOMPLETE;
	}
	return dir;
}