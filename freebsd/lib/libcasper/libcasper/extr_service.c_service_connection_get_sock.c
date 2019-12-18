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
struct service_connection {scalar_t__ sc_magic; int /*<<< orphan*/  sc_chan; } ;

/* Variables and functions */
 scalar_t__ SERVICE_CONNECTION_MAGIC ; 
 int /*<<< orphan*/  assert (int) ; 
 int cap_sock (int /*<<< orphan*/ ) ; 

int
service_connection_get_sock(const struct service_connection *sconn)
{

	assert(sconn->sc_magic == SERVICE_CONNECTION_MAGIC);

	return (cap_sock(sconn->sc_chan));
}