#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  message; } ;
struct TYPE_6__ {TYPE_1__ error_msg; int /*<<< orphan*/  oom; } ;
typedef  TYPE_2__ git_error_state ;

/* Variables and functions */
 int /*<<< orphan*/  git__free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

void git_error_state_free(git_error_state *state)
{
	if (!state)
		return;

	if (!state->oom)
		git__free(state->error_msg.message);

	memset(state, 0, sizeof(git_error_state));
}