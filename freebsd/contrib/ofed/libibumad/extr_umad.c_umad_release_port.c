#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  portnum; int /*<<< orphan*/  ca_name; } ;
typedef  TYPE_1__ umad_port_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ENODEV ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int release_port (TYPE_1__*) ; 

int umad_release_port(umad_port_t * port)
{
	int r;

	TRACE("port %s:%d", port->ca_name, port->portnum);
	if (!port)
		return -ENODEV;

	if ((r = release_port(port)) < 0)
		return r;

	DEBUG("releasing %s:%d", port->ca_name, port->portnum);
	return 0;
}