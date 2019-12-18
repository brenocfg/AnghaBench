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
struct child_process {int dummy; } ;

/* Variables and functions */
 int finish_command (struct child_process*) ; 
 int /*<<< orphan*/  free (struct child_process*) ; 
 scalar_t__ git_connection_is_socket (struct child_process*) ; 

int finish_connect(struct child_process *conn)
{
	int code;
	if (!conn || git_connection_is_socket(conn))
		return 0;

	code = finish_command(conn);
	free(conn);
	return code;
}