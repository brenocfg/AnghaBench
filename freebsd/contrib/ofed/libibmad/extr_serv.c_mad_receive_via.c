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
struct ibmad_port {int /*<<< orphan*/  port_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG (char*,int /*<<< orphan*/ ) ; 
 int IB_MAD_SIZE ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  mad_get_timeout (struct ibmad_port*,int) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 void* umad_alloc (int,scalar_t__) ; 
 int /*<<< orphan*/  umad_free (void*) ; 
 int umad_recv (int /*<<< orphan*/ ,void*,int*,int /*<<< orphan*/ ) ; 
 scalar_t__ umad_size () ; 

void *mad_receive_via(void *umad, int timeout, struct ibmad_port *srcport)
{
	void *mad = umad ? umad : umad_alloc(1, umad_size() + IB_MAD_SIZE);
	int agent;
	int length = IB_MAD_SIZE;

	if ((agent = umad_recv(srcport->port_id, mad, &length,
			       mad_get_timeout(srcport, timeout))) < 0) {
		if (!umad)
			umad_free(mad);
		DEBUG("recv failed: %s", strerror(errno));
		return 0;
	}

	return mad;
}