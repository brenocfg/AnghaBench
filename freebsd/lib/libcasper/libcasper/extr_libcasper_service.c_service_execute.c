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
struct service {int dummy; } ;
struct casper_service {struct service* cs_service; } ;
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 int /*<<< orphan*/  _exit (int) ; 
 int /*<<< orphan*/  nvlist_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvlist_exists_string (int /*<<< orphan*/ *,char*) ; 
 char* nvlist_get_string (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * nvlist_recv (int,int /*<<< orphan*/ ) ; 
 int nvlist_take_descriptor (int /*<<< orphan*/ *,char*) ; 
 struct casper_service* service_find (char const*) ; 
 int /*<<< orphan*/  service_start (struct service*,int,int) ; 

void
service_execute(int chanfd)
{
	struct casper_service *casserv;
	struct service *service;
	const char *servname;
	nvlist_t *nvl;
	int procfd;

	nvl = nvlist_recv(chanfd, 0);
	if (nvl == NULL)
		_exit(1);
	if (!nvlist_exists_string(nvl, "service"))
		_exit(1);
	servname = nvlist_get_string(nvl, "service");
	casserv = service_find(servname);
	if (casserv == NULL)
		_exit(1);
	service = casserv->cs_service;
	procfd = nvlist_take_descriptor(nvl, "procfd");
	nvlist_destroy(nvl);

	service_start(service, chanfd, procfd);
	/* Not reached. */
	_exit(1);
}