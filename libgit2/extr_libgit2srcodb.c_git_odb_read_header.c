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
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_odb_object ;
typedef  int /*<<< orphan*/  git_odb ;
typedef  int /*<<< orphan*/  git_object_t ;

/* Variables and functions */
 int git_odb__read_header_or_object (int /*<<< orphan*/ **,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  git_odb_object_free (int /*<<< orphan*/ *) ; 

int git_odb_read_header(size_t *len_p, git_object_t *type_p, git_odb *db, const git_oid *id)
{
	int error;
	git_odb_object *object;

	error = git_odb__read_header_or_object(&object, len_p, type_p, db, id);

	if (object)
		git_odb_object_free(object);

	return error;
}