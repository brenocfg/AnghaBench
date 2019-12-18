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
struct repository {int dummy; } ;
struct object_id {int dummy; } ;
struct object {int dummy; } ;
struct commit {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  OBJ_COMMIT ; 
 struct object* deref_tag (struct repository*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct commit* object_as_type (struct repository*,struct object*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  parse_object (struct repository*,struct object_id const*) ; 

struct commit *lookup_commit_reference_gently(struct repository *r,
		const struct object_id *oid, int quiet)
{
	struct object *obj = deref_tag(r,
				       parse_object(r, oid),
				       NULL, 0);

	if (!obj)
		return NULL;
	return object_as_type(r, obj, OBJ_COMMIT, quiet);
}