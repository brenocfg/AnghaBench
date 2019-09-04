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
struct has_commit_data {int /*<<< orphan*/  path; int /*<<< orphan*/  result; int /*<<< orphan*/  repo; } ;
typedef  enum object_type { ____Placeholder_object_type } object_type ;

/* Variables and functions */
#define  OBJ_BAD 129 
#define  OBJ_COMMIT 128 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int oid_object_info (int /*<<< orphan*/ ,struct object_id const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  oid_to_hex (struct object_id const*) ; 
 int /*<<< orphan*/  type_name (int) ; 

__attribute__((used)) static int check_has_commit(const struct object_id *oid, void *data)
{
	struct has_commit_data *cb = data;

	enum object_type type = oid_object_info(cb->repo, oid, NULL);

	switch (type) {
	case OBJ_COMMIT:
		return 0;
	case OBJ_BAD:
		/*
		 * Object is missing or invalid. If invalid, an error message
		 * has already been printed.
		 */
		cb->result = 0;
		return 0;
	default:
		die(_("submodule entry '%s' (%s) is a %s, not a commit"),
		    cb->path, oid_to_hex(oid), type_name(type));
	}
}