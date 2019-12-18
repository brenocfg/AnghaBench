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
struct sockaddr {int dummy; } ;
struct rdma_cm_id {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int ERR (int /*<<< orphan*/ ) ; 
 int rdma_join_multicast2 (struct rdma_cm_id*,struct sockaddr*,int,void*) ; 
 int ucma_addrlen (struct sockaddr*) ; 

int rdma_join_multicast(struct rdma_cm_id *id, struct sockaddr *addr,
			void *context)
{
	int addrlen;
	
	addrlen = ucma_addrlen(addr);
	if (!addrlen)
		return ERR(EINVAL);

	return rdma_join_multicast2(id, addr, addrlen, context);
}