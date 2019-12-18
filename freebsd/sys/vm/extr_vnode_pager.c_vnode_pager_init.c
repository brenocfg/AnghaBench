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

/* Variables and functions */
 int /*<<< orphan*/  TUNABLE_INT_FETCH (char*,int*) ; 
 int nswbuf ; 
 int nvnpbufs ; 
 int /*<<< orphan*/  pbuf_zsecond_create (char*,int) ; 
 int /*<<< orphan*/  vnode_pbuf_zone ; 

__attribute__((used)) static void
vnode_pager_init(void *dummy)
{

#ifdef __LP64__
	nvnpbufs = nswbuf * 2;
#else
	nvnpbufs = nswbuf / 2;
#endif
	TUNABLE_INT_FETCH("vm.vnode_pbufs", &nvnpbufs);
	vnode_pbuf_zone = pbuf_zsecond_create("vnpbuf", nvnpbufs);
}