#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct foreach_state {int /*<<< orphan*/  data; int /*<<< orphan*/  (* cb ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;scalar_t__ dir_len; } ;
typedef  int /*<<< orphan*/  git_oid ;
struct TYPE_3__ {scalar_t__ ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 scalar_t__ filename_to_oid (int /*<<< orphan*/ *,scalar_t__) ; 
 int git_error_set_after_callback_function (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int foreach_object_dir_cb(void *_state, git_buf *path)
{
	git_oid oid;
	struct foreach_state *state = (struct foreach_state *) _state;

	if (filename_to_oid(&oid, path->ptr + state->dir_len) < 0)
		return 0;

	return git_error_set_after_callback_function(
		state->cb(&oid, state->data), "git_odb_foreach");
}