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
typedef  void* uint16_t ;
struct vmctx {int /*<<< orphan*/  fd; } ;
struct vm_cpu_topology {void* maxcpus; void* threads; void* cores; void* sockets; } ;

/* Variables and functions */
 int /*<<< orphan*/  VM_SET_TOPOLOGY ; 
 int /*<<< orphan*/  bzero (struct vm_cpu_topology*,int) ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vm_cpu_topology*) ; 

int
vm_set_topology(struct vmctx *ctx,
    uint16_t sockets, uint16_t cores, uint16_t threads, uint16_t maxcpus)
{
	struct vm_cpu_topology topology;

	bzero(&topology, sizeof (struct vm_cpu_topology));
	topology.sockets = sockets;
	topology.cores = cores;
	topology.threads = threads;
	topology.maxcpus = maxcpus;
	return (ioctl(ctx->fd, VM_SET_TOPOLOGY, &topology));
}