#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct daemon_remote {TYPE_1__* worker; } ;
struct TYPE_2__ {int /*<<< orphan*/  base; scalar_t__ need_to_exit; } ;
typedef  int /*<<< orphan*/  RES ;

/* Variables and functions */
 int /*<<< orphan*/  comm_base_exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_ok (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
do_reload(RES* ssl, struct daemon_remote* rc)
{
	rc->worker->need_to_exit = 0;
	comm_base_exit(rc->worker->base);
	send_ok(ssl);
}