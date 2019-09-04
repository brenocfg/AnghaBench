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
struct snapshot {int dummy; } ;
struct packed_ref_store {struct snapshot* snapshot; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 struct snapshot* create_snapshot (struct packed_ref_store*) ; 
 int /*<<< orphan*/  is_lock_file_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  validate_snapshot (struct packed_ref_store*) ; 

__attribute__((used)) static struct snapshot *get_snapshot(struct packed_ref_store *refs)
{
	if (!is_lock_file_locked(&refs->lock))
		validate_snapshot(refs);

	if (!refs->snapshot)
		refs->snapshot = create_snapshot(refs);

	return refs->snapshot;
}