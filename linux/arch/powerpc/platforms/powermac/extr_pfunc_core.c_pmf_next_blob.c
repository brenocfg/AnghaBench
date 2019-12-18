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
struct pmf_cmd {int cmdend; int cmdptr; int error; } ;

/* Variables and functions */

__attribute__((used)) static const void* pmf_next_blob(struct pmf_cmd *cmd, int count)
{
	const void *value;
	if ((cmd->cmdend - cmd->cmdptr) < count) {
		cmd->error = 1;
		return NULL;
	}
	value = cmd->cmdptr;
	cmd->cmdptr += count;
	return value;
}