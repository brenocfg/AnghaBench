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
struct ssh {int dummy; } ;
typedef  int /*<<< orphan*/  Session ;

/* Variables and functions */
 scalar_t__ do_exec (struct ssh*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  packet_check_eom () ; 

__attribute__((used)) static int
session_shell_req(struct ssh *ssh, Session *s)
{
	packet_check_eom();
	return do_exec(ssh, s, NULL) == 0;
}