#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct replay_opts {scalar_t__ action; } ;

/* Variables and functions */
 scalar_t__ REPLAY_REVERT ; 

__attribute__((used)) static const char *action_name(const struct replay_opts *opts)
{
	return opts->action == REPLAY_REVERT ? "revert" : "cherry-pick";
}