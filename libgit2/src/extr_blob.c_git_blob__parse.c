#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_odb_object ;
typedef  int /*<<< orphan*/  git_cached_obj ;
struct TYPE_4__ {int /*<<< orphan*/ * odb; } ;
struct TYPE_5__ {TYPE_1__ data; scalar_t__ raw; } ;
typedef  TYPE_2__ git_blob ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_2__*) ; 
 int /*<<< orphan*/  git_cached_obj_incref (int /*<<< orphan*/ *) ; 

int git_blob__parse(void *_blob, git_odb_object *odb_obj)
{
	git_blob *blob = (git_blob *) _blob;
	assert(blob);
	git_cached_obj_incref((git_cached_obj *)odb_obj);
	blob->raw = 0;
	blob->data.odb = odb_obj;
	return 0;
}