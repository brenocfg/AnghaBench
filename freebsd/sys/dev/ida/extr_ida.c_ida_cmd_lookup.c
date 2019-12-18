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
struct cmd_info {int cmd; } ;

/* Variables and functions */
 struct cmd_info* ci_list ; 

__attribute__((used)) static struct cmd_info *
ida_cmd_lookup (int command)
{
	struct cmd_info *ci;

	ci = ci_list;
	while (ci->cmd) {
		if (ci->cmd == command)
			return (ci);
		ci++;
	}
	return (NULL);
}