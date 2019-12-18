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
typedef  scalar_t__ uint16_t ;
struct vm {scalar_t__ maxcpus; scalar_t__ threads; scalar_t__ cores; scalar_t__ sockets; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ VM_MAXCPU ; 

int
vm_set_topology(struct vm *vm, uint16_t sockets, uint16_t cores,
    uint16_t threads, uint16_t maxcpus)
{
	if (maxcpus != 0)
		return (EINVAL);	/* XXX remove when supported */
	if ((sockets * cores * threads) > vm->maxcpus)
		return (EINVAL);
	/* XXX need to check sockets * cores * threads == vCPU, how? */
	vm->sockets = sockets;
	vm->cores = cores;
	vm->threads = threads;
	vm->maxcpus = VM_MAXCPU;	/* XXX temp to keep code working */
	return(0);
}