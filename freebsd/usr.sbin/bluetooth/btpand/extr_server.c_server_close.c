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

/* Variables and functions */
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  event_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_info (char*) ; 
 int /*<<< orphan*/  server_ev ; 
 int server_fd ; 

__attribute__((used)) static void
server_close(void)
{

	event_del(&server_ev);
	close(server_fd);
	server_fd = -1;

	log_info("server socket closed");
}