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
 int UINT8_MAX ; 
 int /*<<< orphan*/  log_debug (char*,int) ; 
 int /*<<< orphan*/  log_info (char*,scalar_t__,int) ; 
 scalar_t__ server_avail ; 
 int /*<<< orphan*/  server_close () ; 
 int server_fd ; 
 int server_limit ; 
 int /*<<< orphan*/  server_open () ; 
 int /*<<< orphan*/  server_register () ; 
 scalar_t__ service_name ; 

void
server_update(int count)
{

	if (server_limit == 0)
		return;

	log_debug("count %d", count);

	server_avail = UINT8_MAX - (count - 1) * UINT8_MAX / server_limit;
	log_info("Service Availability: %d/%d", server_avail, UINT8_MAX);

	if (server_avail == 0 && server_fd != -1)
		server_close();

	if (server_avail > 0 && server_fd == -1)
		server_open();

	if (service_name)
		server_register();
}