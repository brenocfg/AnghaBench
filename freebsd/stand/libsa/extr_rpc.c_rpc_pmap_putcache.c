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
typedef  void* u_int ;
struct in_addr {int dummy; } ;
struct pmap_list {int port; void* vers; void* prog; struct in_addr addr; } ;

/* Variables and functions */
 size_t PMAP_NUM ; 
 int /*<<< orphan*/  printf (char*) ; 
 struct pmap_list* rpc_pmap_list ; 
 size_t rpc_pmap_num ; 

void
rpc_pmap_putcache(struct in_addr addr, u_int prog, u_int vers, int port)
{
	struct pmap_list *pl;

	/* Don't overflow cache... */
	if (rpc_pmap_num >= PMAP_NUM) {
		/* ... just re-use the last entry. */
		rpc_pmap_num = PMAP_NUM - 1;
#ifdef	RPC_DEBUG
		printf("rpc_pmap_putcache: cache overflow\n");
#endif
	}

	pl = &rpc_pmap_list[rpc_pmap_num];
	rpc_pmap_num++;

	/* Cache answer */
	pl->addr = addr;
	pl->prog = prog;
	pl->vers = vers;
	pl->port = port;
}