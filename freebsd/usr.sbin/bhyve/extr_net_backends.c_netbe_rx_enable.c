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
struct net_backend {void (* recv_enable ) (struct net_backend*) ;} ;

/* Variables and functions */
 void stub1 (struct net_backend*) ; 

void
netbe_rx_enable(struct net_backend *be)
{

	return be->recv_enable(be);
}