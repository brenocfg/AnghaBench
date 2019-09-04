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
struct packed_ref_store {struct snapshot* snapshot; } ;

/* Variables and functions */
 int /*<<< orphan*/  release_snapshot (struct snapshot*) ; 

__attribute__((used)) static void clear_snapshot(struct packed_ref_store *refs)
{
	if (refs->snapshot) {
		struct snapshot *snapshot = refs->snapshot;

		refs->snapshot = NULL;
		release_snapshot(snapshot);
	}
}