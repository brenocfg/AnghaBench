#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  data; int /*<<< orphan*/  len; int /*<<< orphan*/  type; } ;
typedef  TYPE_2__ git_rawobj ;
typedef  int /*<<< orphan*/  git_oid ;
struct TYPE_7__ {int /*<<< orphan*/  size; int /*<<< orphan*/  type; int /*<<< orphan*/  oid; } ;
struct TYPE_9__ {int /*<<< orphan*/  buffer; TYPE_1__ cached; } ;
typedef  TYPE_3__ git_odb_object ;

/* Variables and functions */
 TYPE_3__* git__calloc (int,int) ; 
 int /*<<< orphan*/  git_oid_cpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static git_odb_object *odb_object__alloc(const git_oid *oid, git_rawobj *source)
{
	git_odb_object *object = git__calloc(1, sizeof(git_odb_object));

	if (object != NULL) {
		git_oid_cpy(&object->cached.oid, oid);
		object->cached.type = source->type;
		object->cached.size = source->len;
		object->buffer      = source->data;
	}

	return object;
}