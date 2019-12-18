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
struct service_connection {scalar_t__ sc_magic; } ;
struct service {scalar_t__ s_magic; int /*<<< orphan*/  s_connections; } ;

/* Variables and functions */
 scalar_t__ SERVICE_CONNECTION_MAGIC ; 
 scalar_t__ SERVICE_MAGIC ; 
 struct service_connection* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 

struct service_connection *
service_connection_first(struct service *service)
{
	struct service_connection *sconn;

	assert(service->s_magic == SERVICE_MAGIC);

	sconn = TAILQ_FIRST(&service->s_connections);
	assert(sconn == NULL ||
	    sconn->sc_magic == SERVICE_CONNECTION_MAGIC);
	return (sconn);
}