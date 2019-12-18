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
struct service {scalar_t__ s_magic; struct service* s_name; } ;

/* Variables and functions */
 scalar_t__ SERVICE_MAGIC ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  free (struct service*) ; 
 struct service_connection* service_connection_first (struct service*) ; 
 int /*<<< orphan*/  service_connection_remove (struct service*,struct service_connection*) ; 

void
service_free(struct service *service)
{
	struct service_connection *sconn;

	assert(service->s_magic == SERVICE_MAGIC);

	service->s_magic = 0;
	while ((sconn = service_connection_first(service)) != NULL)
		service_connection_remove(service, sconn);
	free(service->s_name);
	free(service);
}