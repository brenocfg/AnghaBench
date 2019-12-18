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
struct repository {int dummy; } ;
struct object_id {int dummy; } ;
struct diff_filespec {int /*<<< orphan*/  path; } ;
struct TYPE_2__ {int /*<<< orphan*/  oid; } ;
struct commit {TYPE_1__ object; } ;

/* Variables and functions */
 int /*<<< orphan*/  die (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fill_filespec (struct diff_filespec*,struct object_id*,int,unsigned short) ; 
 scalar_t__ get_tree_entry (struct repository*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct object_id*,unsigned short*) ; 

__attribute__((used)) static void fill_blob_sha1(struct repository *r, struct commit *commit,
			   struct diff_filespec *spec)
{
	unsigned short mode;
	struct object_id oid;

	if (get_tree_entry(r, &commit->object.oid, spec->path, &oid, &mode))
		die("There is no path %s in the commit", spec->path);
	fill_filespec(spec, &oid, 1, mode);

	return;
}