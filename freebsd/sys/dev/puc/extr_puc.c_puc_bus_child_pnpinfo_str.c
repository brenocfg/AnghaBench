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
struct puc_port {int p_type; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct puc_port* device_get_ivars (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,int) ; 

int
puc_bus_child_pnpinfo_str(device_t dev, device_t child, char *buf,
    size_t buflen)
{
	struct puc_port *port;

	port = device_get_ivars(child);
	snprintf(buf, buflen, "type=%d", port->p_type);
	return (0);
}