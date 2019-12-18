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
 int /*<<< orphan*/  in_pfsync_protosw ; 
 int ipproto_register (int /*<<< orphan*/ ) ; 
 int pf_proto_register (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pf_proto_unregister (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfsync_detach_ifnet ; 
 int /*<<< orphan*/  pfsync_detach_ifnet_ptr ; 

__attribute__((used)) static int
pfsync_init()
{
#ifdef INET
	int error;

	pfsync_detach_ifnet_ptr = pfsync_detach_ifnet;

	error = pf_proto_register(PF_INET, &in_pfsync_protosw);
	if (error)
		return (error);
	error = ipproto_register(IPPROTO_PFSYNC);
	if (error) {
		pf_proto_unregister(PF_INET, IPPROTO_PFSYNC, SOCK_RAW);
		return (error);
	}
#endif

	return (0);
}