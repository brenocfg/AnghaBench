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
struct service_connection {scalar_t__ sc_magic; int /*<<< orphan*/  sc_chan; int /*<<< orphan*/  sc_limits; } ;
struct service {scalar_t__ s_magic; int /*<<< orphan*/  s_connections; } ;

/* Variables and functions */
 scalar_t__ SERVICE_CONNECTION_MAGIC ; 
 scalar_t__ SERVICE_MAGIC ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct service_connection*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  cap_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct service_connection*) ; 
 int /*<<< orphan*/  nvlist_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sc_next ; 

void
service_connection_remove(struct service *service,
    struct service_connection *sconn)
{

	assert(service->s_magic == SERVICE_MAGIC);
	assert(sconn->sc_magic == SERVICE_CONNECTION_MAGIC);

	TAILQ_REMOVE(&service->s_connections, sconn, sc_next);
	sconn->sc_magic = 0;
	nvlist_destroy(sconn->sc_limits);
	cap_close(sconn->sc_chan);
	free(sconn);
}