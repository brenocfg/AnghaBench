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
struct service_connection {scalar_t__ sc_magic; int /*<<< orphan*/ * sc_limits; } ;
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 scalar_t__ SERVICE_CONNECTION_MAGIC ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  nvlist_destroy (int /*<<< orphan*/ *) ; 

void
service_connection_set_limits(struct service_connection *sconn,
    nvlist_t *limits)
{

	assert(sconn->sc_magic == SERVICE_CONNECTION_MAGIC);

	nvlist_destroy(sconn->sc_limits);
	sconn->sc_limits = limits;
}