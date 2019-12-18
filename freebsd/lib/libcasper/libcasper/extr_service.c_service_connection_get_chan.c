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
struct service_connection {scalar_t__ sc_magic; int /*<<< orphan*/ * sc_chan; } ;
typedef  int /*<<< orphan*/  cap_channel_t ;

/* Variables and functions */
 scalar_t__ SERVICE_CONNECTION_MAGIC ; 
 int /*<<< orphan*/  assert (int) ; 

cap_channel_t *
service_connection_get_chan(const struct service_connection *sconn)
{

	assert(sconn->sc_magic == SERVICE_CONNECTION_MAGIC);

	return (sconn->sc_chan);
}