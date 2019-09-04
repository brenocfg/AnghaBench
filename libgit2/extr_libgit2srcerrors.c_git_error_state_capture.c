#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_7__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  message; int /*<<< orphan*/  klass; } ;
struct TYPE_9__ {int error_code; int oom; TYPE_1__ error_msg; } ;
typedef  TYPE_2__ git_error_state ;
struct TYPE_10__ {int /*<<< orphan*/  message; int /*<<< orphan*/  klass; } ;
typedef  TYPE_3__ git_error ;
typedef  int /*<<< orphan*/  git_buf ;
struct TYPE_11__ {int /*<<< orphan*/  error_buf; TYPE_3__* last_error; } ;

/* Variables and functions */
 TYPE_7__* GIT_GLOBAL ; 
 TYPE_3__ g_git_oom_error ; 
 int /*<<< orphan*/  git_buf_detach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_error_clear () ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

int git_error_state_capture(git_error_state *state, int error_code)
{
	git_error *error = GIT_GLOBAL->last_error;
	git_buf *error_buf = &GIT_GLOBAL->error_buf;

	memset(state, 0, sizeof(git_error_state));

	if (!error_code)
		return 0;

	state->error_code = error_code;
	state->oom = (error == &g_git_oom_error);

	if (error) {
		state->error_msg.klass = error->klass;

		if (state->oom)
			state->error_msg.message = g_git_oom_error.message;
		else
			state->error_msg.message = git_buf_detach(error_buf);
	}

	git_error_clear();
	return error_code;
}