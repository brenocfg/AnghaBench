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
struct commit_array {int nr; scalar_t__* commits; int /*<<< orphan*/  alloc; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_GROW (scalar_t__*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ lookup_commit_reference_gently (int /*<<< orphan*/ ,struct object_id const*,int) ; 
 int /*<<< orphan*/  the_repository ; 

__attribute__((used)) static int add_ref(const char *refname, const struct object_id *oid,
		   int flags, void *cb_data)
{
	struct commit_array *ca = cb_data;
	ALLOC_GROW(ca->commits, ca->nr + 1, ca->alloc);
	ca->commits[ca->nr] = lookup_commit_reference_gently(the_repository,
							     oid, 1);
	if (ca->commits[ca->nr])
		ca->nr++;
	return 0;
}