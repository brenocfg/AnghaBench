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
struct pending_tcp {int /*<<< orphan*/  c; struct pending_tcp* next_free; } ;
struct outside_network {int num_tcp; struct pending_tcp** tcp_conns; int /*<<< orphan*/  base; struct pending_tcp* tcp_free; } ;

/* Variables and functions */
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  comm_point_create_tcp_out (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,struct pending_tcp*) ; 
 int /*<<< orphan*/  outnet_tcp_cb ; 

__attribute__((used)) static int
create_pending_tcp(struct outside_network* outnet, size_t bufsize)
{
	size_t i;
	if(outnet->num_tcp == 0)
		return 1; /* no tcp needed, nothing to do */
	if(!(outnet->tcp_conns = (struct pending_tcp **)calloc(
			outnet->num_tcp, sizeof(struct pending_tcp*))))
		return 0;
	for(i=0; i<outnet->num_tcp; i++) {
		if(!(outnet->tcp_conns[i] = (struct pending_tcp*)calloc(1, 
			sizeof(struct pending_tcp))))
			return 0;
		outnet->tcp_conns[i]->next_free = outnet->tcp_free;
		outnet->tcp_free = outnet->tcp_conns[i];
		outnet->tcp_conns[i]->c = comm_point_create_tcp_out(
			outnet->base, bufsize, outnet_tcp_cb, 
			outnet->tcp_conns[i]);
		if(!outnet->tcp_conns[i]->c)
			return 0;
	}
	return 1;
}