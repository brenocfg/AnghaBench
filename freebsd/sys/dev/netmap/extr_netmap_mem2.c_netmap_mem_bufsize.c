#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct netmap_mem_d {TYPE_1__* pools; } ;
struct TYPE_2__ {int _objsize; } ;

/* Variables and functions */
 size_t NETMAP_BUF_POOL ; 

unsigned
netmap_mem_bufsize(struct netmap_mem_d *nmd)
{
	return nmd->pools[NETMAP_BUF_POOL]._objsize;
}