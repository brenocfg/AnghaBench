#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct notes_merge_pair {int /*<<< orphan*/  obj; int /*<<< orphan*/  remote; int /*<<< orphan*/  local; int /*<<< orphan*/  base; } ;
struct notes_merge_options {TYPE_1__* repo; int /*<<< orphan*/  remote_ref; int /*<<< orphan*/  local_ref; } ;
struct TYPE_10__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_2__ mmfile_t ;
struct TYPE_11__ {int /*<<< orphan*/  ptr; int /*<<< orphan*/  size; } ;
typedef  TYPE_3__ mmbuffer_t ;
struct TYPE_9__ {int /*<<< orphan*/  index; } ;

/* Variables and functions */
 int /*<<< orphan*/  die (char*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int ll_merge (TYPE_3__*,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  oid_to_hex (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_mmblob (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_buf_to_worktree (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ll_merge_in_worktree(struct notes_merge_options *o,
				struct notes_merge_pair *p)
{
	mmbuffer_t result_buf;
	mmfile_t base, local, remote;
	int status;

	read_mmblob(&base, &p->base);
	read_mmblob(&local, &p->local);
	read_mmblob(&remote, &p->remote);

	status = ll_merge(&result_buf, oid_to_hex(&p->obj), &base, NULL,
			  &local, o->local_ref, &remote, o->remote_ref,
			  o->repo->index, NULL);

	free(base.ptr);
	free(local.ptr);
	free(remote.ptr);

	if ((status < 0) || !result_buf.ptr)
		die("Failed to execute internal merge");

	write_buf_to_worktree(&p->obj, result_buf.ptr, result_buf.size);
	free(result_buf.ptr);

	return status;
}