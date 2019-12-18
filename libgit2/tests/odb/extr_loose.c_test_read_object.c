#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  id; } ;
typedef  TYPE_2__ object_data ;
struct TYPE_13__ {int /*<<< orphan*/  type; int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
typedef  TYPE_3__ git_rawobj ;
typedef  int /*<<< orphan*/  git_oid ;
struct TYPE_11__ {int /*<<< orphan*/  type; int /*<<< orphan*/  size; } ;
struct TYPE_14__ {TYPE_1__ cached; int /*<<< orphan*/  buffer; } ;
typedef  TYPE_4__ git_odb_object ;
typedef  int /*<<< orphan*/  git_odb ;

/* Variables and functions */
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmp_objects (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  git_odb_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_odb_object_free (TYPE_4__*) ; 
 int /*<<< orphan*/  git_odb_open (int /*<<< orphan*/ **,char*) ; 
 int /*<<< orphan*/  git_odb_read (TYPE_4__**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_object_files (TYPE_2__*) ; 

__attribute__((used)) static void test_read_object(object_data *data)
{
    git_oid id;
    git_odb_object *obj;
	git_odb *odb;
	git_rawobj tmp;

    write_object_files(data);

    cl_git_pass(git_odb_open(&odb, "test-objects"));
    cl_git_pass(git_oid_fromstr(&id, data->id));
    cl_git_pass(git_odb_read(&obj, odb, &id));

	tmp.data = obj->buffer;
	tmp.len = obj->cached.size;
	tmp.type = obj->cached.type;

    cmp_objects(&tmp, data);

    git_odb_object_free(obj);
	git_odb_free(odb);
}