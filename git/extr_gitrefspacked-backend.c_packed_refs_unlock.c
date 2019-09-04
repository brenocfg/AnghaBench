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
struct ref_store {int dummy; } ;
struct packed_ref_store {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG (char*) ; 
 int REF_STORE_READ ; 
 int REF_STORE_WRITE ; 
 int /*<<< orphan*/  is_lock_file_locked (int /*<<< orphan*/ *) ; 
 struct packed_ref_store* packed_downcast (struct ref_store*,int,char*) ; 
 int /*<<< orphan*/  rollback_lock_file (int /*<<< orphan*/ *) ; 

void packed_refs_unlock(struct ref_store *ref_store)
{
	struct packed_ref_store *refs = packed_downcast(
			ref_store,
			REF_STORE_READ | REF_STORE_WRITE,
			"packed_refs_unlock");

	if (!is_lock_file_locked(&refs->lock))
		BUG("packed_refs_unlock() called when not locked");
	rollback_lock_file(&refs->lock);
}