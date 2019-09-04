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
struct TYPE_8__ {int seconds; } ;
struct TYPE_7__ {int seconds; } ;
struct TYPE_9__ {int mode; char* path; int /*<<< orphan*/  id; scalar_t__ file_size; TYPE_2__ mtime; TYPE_1__ ctime; } ;
typedef  TYPE_3__ git_index_entry ;
typedef  int /*<<< orphan*/  entry ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_INDEX_ENTRY_STAGE_SET (TYPE_3__*,int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_empty_id ; 
 int /*<<< orphan*/  g_index ; 
 int /*<<< orphan*/  git_index_add (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  git_oid_cpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 

void test_index_collision__add_with_highstage_2(void)
{
	git_index_entry entry;

	memset(&entry, 0, sizeof(entry));
	entry.ctime.seconds = 12346789;
	entry.mtime.seconds = 12346789;
	entry.mode  = 0100644;
	entry.file_size = 0;
	git_oid_cpy(&entry.id, &g_empty_id);

	entry.path = "a/b/c";
	GIT_INDEX_ENTRY_STAGE_SET(&entry, 1);
	cl_git_pass(git_index_add(g_index, &entry));

	/* create a blob beneath the previous tree entry */
	entry.path = "a/b/c";
	GIT_INDEX_ENTRY_STAGE_SET(&entry, 2);
	cl_git_pass(git_index_add(g_index, &entry));

	/* create another tree entry above the blob */
	entry.path = "a/b";
	GIT_INDEX_ENTRY_STAGE_SET(&entry, 3);
	cl_git_pass(git_index_add(g_index, &entry));
}