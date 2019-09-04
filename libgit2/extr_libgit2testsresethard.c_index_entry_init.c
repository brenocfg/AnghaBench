#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_oid ;
struct TYPE_5__ {char* path; int mode; int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ git_index_entry ;
typedef  int /*<<< orphan*/  git_index ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_INDEX_ENTRY_STAGE_SET (TYPE_1__*,int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_index_add (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  git_oid_cpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int,int) ; 

__attribute__((used)) static void index_entry_init(git_index *index, int side, git_oid *oid)
{
	git_index_entry entry;

	memset(&entry, 0x0, sizeof(git_index_entry));

	entry.path = "conflicting_file";
	GIT_INDEX_ENTRY_STAGE_SET(&entry, side);
	entry.mode = 0100644;
	git_oid_cpy(&entry.id, oid);

	cl_git_pass(git_index_add(index, &entry));
}