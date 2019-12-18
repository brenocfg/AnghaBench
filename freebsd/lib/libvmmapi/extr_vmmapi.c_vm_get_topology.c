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
typedef  int /*<<< orphan*/  uint16_t ;
struct vmctx {int /*<<< orphan*/  fd; } ;
struct vm_cpu_topology {int /*<<< orphan*/  maxcpus; int /*<<< orphan*/  threads; int /*<<< orphan*/  cores; int /*<<< orphan*/  sockets; } ;

/* Variables and functions */
 int /*<<< orphan*/  VM_GET_TOPOLOGY ; 
 int /*<<< orphan*/  bzero (struct vm_cpu_topology*,int) ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vm_cpu_topology*) ; 

int
vm_get_topology(struct vmctx *ctx,
    uint16_t *sockets, uint16_t *cores, uint16_t *threads, uint16_t *maxcpus)
{
	struct vm_cpu_topology topology;
	int error;

	bzero(&topology, sizeof (struct vm_cpu_topology));
	error = ioctl(ctx->fd, VM_GET_TOPOLOGY, &topology);
	if (error == 0) {
		*sockets = topology.sockets;
		*cores = topology.cores;
		*threads = topology.threads;
		*maxcpus = topology.maxcpus;
	}
	return (error);
}