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
typedef  int /*<<< orphan*/  git_odb ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ git_odb__add_default_backends (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_odb_free (int /*<<< orphan*/ *) ; 
 scalar_t__ git_odb_new (int /*<<< orphan*/ **) ; 

int git_odb_open(git_odb **out, const char *objects_dir)
{
	git_odb *db;

	assert(out && objects_dir);

	*out = NULL;

	if (git_odb_new(&db) < 0)
		return -1;

	if (git_odb__add_default_backends(db, objects_dir, 0, 0) < 0) {
		git_odb_free(db);
		return -1;
	}

	*out = db;
	return 0;
}