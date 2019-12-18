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
struct netmap_hw_adapter {int dummy; } ;
struct netmap_adapter {int dummy; } ;

/* Variables and functions */
 int netmap_attach_ext (struct netmap_adapter*,int,int) ; 

int
netmap_attach(struct netmap_adapter *arg)
{
	return netmap_attach_ext(arg, sizeof(struct netmap_hw_adapter),
			1 /* override nm_reg */);
}