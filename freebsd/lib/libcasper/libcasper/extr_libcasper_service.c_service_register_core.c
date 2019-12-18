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
struct service_connection {int dummy; } ;
struct casper_service {int /*<<< orphan*/  cs_service; } ;

/* Variables and functions */
 int /*<<< orphan*/  CORE_CASPER_NAME ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  casper_command ; 
 int /*<<< orphan*/  casper_limit ; 
 int /*<<< orphan*/  close (int) ; 
 struct service_connection* service_connection_add (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 struct casper_service* service_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
service_register_core(int fd)
{
	struct casper_service *casserv;
	struct service_connection *sconn;

	casserv = service_register(CORE_CASPER_NAME, casper_limit,
	    casper_command, 0);
	sconn = service_connection_add(casserv->cs_service, fd, NULL);
	if (sconn == NULL) {
		close(fd);
		abort();
	}
}