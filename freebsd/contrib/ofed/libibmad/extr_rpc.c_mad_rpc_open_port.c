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
typedef  int uint8_t ;
struct ibmad_port {int port_id; int portnum; struct ibmad_port* class_agents; int /*<<< orphan*/  ca_name; } ;

/* Variables and functions */
 scalar_t__ EINVAL ; 
 scalar_t__ EIO ; 
 scalar_t__ ENODEV ; 
 scalar_t__ ENOMEM ; 
 int /*<<< orphan*/  IBWARN (char*,...) ; 
 int IB_SA_CLASS ; 
 int MAX_CLASS ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  free (struct ibmad_port*) ; 
 scalar_t__ mad_register_client_via (int,int,struct ibmad_port*) ; 
 struct ibmad_port* malloc (int) ; 
 int /*<<< orphan*/  memset (struct ibmad_port*,int,int) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  umad_close_port (int) ; 
 scalar_t__ umad_init () ; 
 int umad_open_port (char*,int) ; 

struct ibmad_port *mad_rpc_open_port(char *dev_name, int dev_port,
				     int *mgmt_classes, int num_classes)
{
	struct ibmad_port *p;
	int port_id;

	if (num_classes >= MAX_CLASS) {
		IBWARN("too many classes %d requested", num_classes);
		errno = EINVAL;
		return NULL;
	}

	if (umad_init() < 0) {
		IBWARN("can't init UMAD library");
		errno = ENODEV;
		return NULL;
	}

	p = malloc(sizeof(*p));
	if (!p) {
		errno = ENOMEM;
		return NULL;
	}
	memset(p, 0, sizeof(*p));

	if ((port_id = umad_open_port(dev_name, dev_port)) < 0) {
		IBWARN("can't open UMAD port (%s:%d)", dev_name, dev_port);
		if (!errno)
			errno = EIO;
		free(p);
		return NULL;
	}

	p->port_id = port_id;
	if (dev_name)
		strncpy(p->ca_name, dev_name, sizeof p->ca_name - 1);
	p->portnum = dev_port;

	memset(p->class_agents, 0xff, sizeof p->class_agents);
	while (num_classes--) {
		uint8_t rmpp_version = 0;
		int mgmt = *mgmt_classes++;

		if (mgmt == IB_SA_CLASS)
			rmpp_version = 1;
		if (mgmt < 0 || mgmt >= MAX_CLASS ||
		    mad_register_client_via(mgmt, rmpp_version, p) < 0) {
			IBWARN("client_register for mgmt %d failed", mgmt);
			if (!errno)
				errno = EINVAL;
			umad_close_port(port_id);
			free(p);
			return NULL;
		}
	}

	return p;
}