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
struct tube {int /*<<< orphan*/ * cmd_msg; int /*<<< orphan*/ * listen_com; } ;

/* Variables and functions */
 int /*<<< orphan*/  comm_point_delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 

void tube_remove_bg_listen(struct tube* tube)
{
	if(tube->listen_com) {
		comm_point_delete(tube->listen_com);
		tube->listen_com = NULL;
	}
	free(tube->cmd_msg);
	tube->cmd_msg = NULL;
}