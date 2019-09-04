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
 int REF_STORE_READ ; 
 int REF_STORE_WRITE ; 
 int is_lock_file_locked (int /*<<< orphan*/ *) ; 
 struct packed_ref_store* packed_downcast (struct ref_store*,int,char*) ; 

int packed_refs_is_locked(struct ref_store *ref_store)
{
	struct packed_ref_store *refs = packed_downcast(
			ref_store,
			REF_STORE_READ | REF_STORE_WRITE,
			"packed_refs_is_locked");

	return is_lock_file_locked(&refs->lock);
}