#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_oid ;
struct TYPE_3__ {scalar_t__ type; scalar_t__ length; int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ git_odb_expand_id ;
typedef  int /*<<< orphan*/  git_odb ;
typedef  scalar_t__ git_object_t ;

/* Variables and functions */
#define  GIT_EAMBIGUOUS 129 
#define  GIT_ENOTFOUND 128 
 scalar_t__ GIT_OBJECT_ANY ; 
 scalar_t__ GIT_OID_HEXSZ ; 
 scalar_t__ GIT_OID_MINPREFIXLEN ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  git_error_clear () ; 
 int /*<<< orphan*/  git_oid_cpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int odb_exists_prefix_1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,int) ; 
 int odb_otype_fast (scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int git_odb_expand_ids(
	git_odb *db,
	git_odb_expand_id *ids,
	size_t count)
{
	size_t i;

	assert(db && ids);

	for (i = 0; i < count; i++) {
		git_odb_expand_id *query = &ids[i];
		int error = GIT_EAMBIGUOUS;

		if (!query->type)
			query->type = GIT_OBJECT_ANY;

		/* if we have a short OID, expand it first */
		if (query->length >= GIT_OID_MINPREFIXLEN && query->length < GIT_OID_HEXSZ) {
			git_oid actual_id;

			error = odb_exists_prefix_1(&actual_id, db, &query->id, query->length, false);
			if (!error) {
				git_oid_cpy(&query->id, &actual_id);
				query->length = GIT_OID_HEXSZ;
			}
		}

		/*
		 * now we ought to have a 40-char OID, either because we've expanded it
		 * or because the user passed a full OID. Ensure its type is right.
		 */
		if (query->length >= GIT_OID_HEXSZ) {
			git_object_t actual_type;

			error = odb_otype_fast(&actual_type, db, &query->id);
			if (!error) {
				if (query->type != GIT_OBJECT_ANY && query->type != actual_type)
					error = GIT_ENOTFOUND;
				else
					query->type = actual_type;
			}
		}

		switch (error) {
		/* no errors, so we've successfully expanded the OID */
		case 0:
			continue;

		/* the object is missing or ambiguous */
		case GIT_ENOTFOUND:
		case GIT_EAMBIGUOUS:
			memset(&query->id, 0, sizeof(git_oid));
			query->length = 0;
			query->type = 0;
			break;

		/* something went very wrong with the ODB; bail hard */
		default:
			return error;
		}
	}

	git_error_clear();
	return 0;
}