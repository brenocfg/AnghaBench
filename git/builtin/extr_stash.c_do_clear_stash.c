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
struct object_id {int dummy; } ;

/* Variables and functions */
 int delete_ref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct object_id*,int /*<<< orphan*/ ) ; 
 scalar_t__ get_oid (int /*<<< orphan*/ ,struct object_id*) ; 
 int /*<<< orphan*/  ref_stash ; 

__attribute__((used)) static int do_clear_stash(void)
{
	struct object_id obj;
	if (get_oid(ref_stash, &obj))
		return 0;

	return delete_ref(NULL, ref_stash, &obj, 0);
}