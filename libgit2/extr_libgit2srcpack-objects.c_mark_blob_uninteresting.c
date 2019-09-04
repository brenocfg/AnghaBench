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
struct walk_object {int uninteresting; } ;
typedef  int /*<<< orphan*/  git_packbuilder ;
typedef  int /*<<< orphan*/  git_oid ;

/* Variables and functions */
 int retrieve_object (struct walk_object**,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int mark_blob_uninteresting(git_packbuilder *pb, const git_oid *id)
{
	int error;
	struct walk_object *obj;

	if ((error = retrieve_object(&obj, pb, id)) < 0)
		return error;

	obj->uninteresting = 1;

	return 0;
}