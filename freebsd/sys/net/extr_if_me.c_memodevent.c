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
typedef  int /*<<< orphan*/  module_t ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  MOD_LOAD 129 
#define  MOD_UNLOAD 128 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  ecookie ; 
 int /*<<< orphan*/  ip_encap_attach (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip_encap_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip_encap_register_srcaddr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip_encap_unregister_srcaddr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  me_encap_cfg ; 
 int /*<<< orphan*/  me_srcaddr ; 
 int /*<<< orphan*/  me_srcaddrtab ; 

__attribute__((used)) static int
memodevent(module_t mod, int type, void *data)
{

	switch (type) {
	case MOD_LOAD:
		me_srcaddrtab = ip_encap_register_srcaddr(me_srcaddr,
		    NULL, M_WAITOK);
		ecookie = ip_encap_attach(&me_encap_cfg, NULL, M_WAITOK);
		break;
	case MOD_UNLOAD:
		ip_encap_detach(ecookie);
		ip_encap_unregister_srcaddr(me_srcaddrtab);
		break;
	default:
		return (EOPNOTSUPP);
	}
	return (0);
}