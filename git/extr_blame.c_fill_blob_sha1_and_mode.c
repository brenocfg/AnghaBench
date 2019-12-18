#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct repository {int dummy; } ;
struct blame_origin {int /*<<< orphan*/  mode; int /*<<< orphan*/  blob_oid; int /*<<< orphan*/  path; TYPE_2__* commit; } ;
struct TYPE_3__ {int /*<<< orphan*/  oid; } ;
struct TYPE_4__ {TYPE_1__ object; } ;

/* Variables and functions */
 scalar_t__ OBJ_BLOB ; 
 int /*<<< orphan*/  S_IFINVALID ; 
 scalar_t__ get_tree_entry (struct repository*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  is_null_oid (int /*<<< orphan*/ *) ; 
 scalar_t__ oid_object_info (struct repository*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  oidclr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fill_blob_sha1_and_mode(struct repository *r,
				   struct blame_origin *origin)
{
	if (!is_null_oid(&origin->blob_oid))
		return 0;
	if (get_tree_entry(r, &origin->commit->object.oid, origin->path, &origin->blob_oid, &origin->mode))
		goto error_out;
	if (oid_object_info(r, &origin->blob_oid, NULL) != OBJ_BLOB)
		goto error_out;
	return 0;
 error_out:
	oidclr(&origin->blob_oid);
	origin->mode = S_IFINVALID;
	return -1;
}