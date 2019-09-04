#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct packed_ref_store {int /*<<< orphan*/  path; TYPE_1__* snapshot; } ;
struct TYPE_2__ {int /*<<< orphan*/  validity; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_snapshot (struct packed_ref_store*) ; 
 int /*<<< orphan*/  stat_validity_check (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void validate_snapshot(struct packed_ref_store *refs)
{
	if (refs->snapshot &&
	    !stat_validity_check(&refs->snapshot->validity, refs->path))
		clear_snapshot(refs);
}