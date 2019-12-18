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

/* Variables and functions */
 scalar_t__ SERVICE_CONNECTION_MAGIC ; 
 struct service_connection* TAILQ_NEXT (struct service_connection*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  sc_next ; 

struct service_connection *
service_connection_next(struct service_connection *sconn)
{

	assert(sconn->sc_magic == SERVICE_CONNECTION_MAGIC);

	sconn = TAILQ_NEXT(sconn, sc_next);
	assert(sconn == NULL ||
	    sconn->sc_magic == SERVICE_CONNECTION_MAGIC);
	return (sconn);
}