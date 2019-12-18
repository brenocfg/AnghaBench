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
typedef  int u_int ;
struct ssh {int dummy; } ;
typedef  int /*<<< orphan*/  Session ;

/* Variables and functions */
 scalar_t__ do_exec (struct ssh*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  packet_check_eom () ; 
 char* packet_get_string (int*) ; 

__attribute__((used)) static int
session_exec_req(struct ssh *ssh, Session *s)
{
	u_int len, success;

	char *command = packet_get_string(&len);
	packet_check_eom();
	success = do_exec(ssh, s, command) == 0;
	free(command);
	return success;
}