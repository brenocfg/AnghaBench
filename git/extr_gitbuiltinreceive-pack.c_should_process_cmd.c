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
struct command {int /*<<< orphan*/  skip_update; int /*<<< orphan*/  error_string; } ;

/* Variables and functions */

__attribute__((used)) static int should_process_cmd(struct command *cmd)
{
	return !cmd->error_string && !cmd->skip_update;
}