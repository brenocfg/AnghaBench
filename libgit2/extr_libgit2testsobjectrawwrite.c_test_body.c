#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/  id; } ;
typedef  TYPE_2__ object_data ;
struct TYPE_16__ {int /*<<< orphan*/  type; int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
typedef  TYPE_3__ git_rawobj ;
typedef  int /*<<< orphan*/  git_oid ;
struct TYPE_14__ {int /*<<< orphan*/  type; int /*<<< orphan*/  size; } ;
struct TYPE_17__ {TYPE_1__ cached; int /*<<< orphan*/  buffer; } ;
typedef  TYPE_4__ git_odb_object ;
typedef  int /*<<< orphan*/  git_odb ;

/* Variables and functions */
 int /*<<< orphan*/  check_object_files (TYPE_2__*) ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmp_objects (TYPE_3__*,TYPE_3__*) ; 
 int /*<<< orphan*/  git_odb_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_odb_object_free (TYPE_4__*) ; 
 int /*<<< orphan*/  git_odb_open (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_odb_read (TYPE_4__**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ git_oid_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_odb_dir () ; 
 int /*<<< orphan*/  odb_dir ; 
 int /*<<< orphan*/  remove_object_files (TYPE_2__*) ; 
 int /*<<< orphan*/  streaming_write (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_3__*) ; 

void test_body(object_data *d, git_rawobj *o)
{
   git_odb *db;
   git_oid id1, id2;
   git_odb_object *obj;
   git_rawobj tmp;

   make_odb_dir();
   cl_git_pass(git_odb_open(&db, odb_dir));
   cl_git_pass(git_oid_fromstr(&id1, d->id));

   streaming_write(&id2, db, o);
   cl_assert(git_oid_cmp(&id1, &id2) == 0);
   check_object_files(d);

   cl_git_pass(git_odb_read(&obj, db, &id1));

   tmp.data = obj->buffer;
   tmp.len = obj->cached.size;
   tmp.type = obj->cached.type;

   cmp_objects(&tmp, o);

   git_odb_object_free(obj);
   git_odb_free(db);
   remove_object_files(d);
}