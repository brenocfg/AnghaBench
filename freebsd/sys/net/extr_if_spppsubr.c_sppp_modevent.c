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
 int EACCES ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  IFT_PPP ; 
#define  MOD_LOAD 129 
#define  MOD_UNLOAD 128 
 int /*<<< orphan*/  if_register_com_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sppp_alloc ; 
 int /*<<< orphan*/  sppp_free ; 

__attribute__((used)) static int
sppp_modevent(module_t mod, int type, void *unused)
{
	switch (type) {
	case MOD_LOAD:
		/*
		 * XXX: should probably be IFT_SPPP, but it's fairly
		 * harmless to allocate struct sppp's for non-sppp
		 * interfaces.
		 */

		if_register_com_alloc(IFT_PPP, sppp_alloc, sppp_free);
		break;
	case MOD_UNLOAD:
		/* if_deregister_com_alloc(IFT_PPP); */
		return EACCES;
	default:
		return EOPNOTSUPP;
	}
	return 0;
}