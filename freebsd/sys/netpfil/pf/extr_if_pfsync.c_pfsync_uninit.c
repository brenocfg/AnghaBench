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
 int /*<<< orphan*/  IPPROTO_PFSYNC ; 
 int /*<<< orphan*/  PF_INET ; 
 int /*<<< orphan*/  SOCK_RAW ; 
 int /*<<< orphan*/  ipproto_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pf_proto_unregister (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pfsync_detach_ifnet_ptr ; 

__attribute__((used)) static void
pfsync_uninit()
{
	pfsync_detach_ifnet_ptr = NULL;

#ifdef INET
	ipproto_unregister(IPPROTO_PFSYNC);
	pf_proto_unregister(PF_INET, IPPROTO_PFSYNC, SOCK_RAW);
#endif
}