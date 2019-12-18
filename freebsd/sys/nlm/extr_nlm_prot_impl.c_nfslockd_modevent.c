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
 int nlm_init () ; 
 int /*<<< orphan*/  nlm_uninit () ; 

__attribute__((used)) static int
nfslockd_modevent(module_t mod, int type, void *data)
{

	switch (type) {
	case MOD_LOAD:
		return (nlm_init());

	case MOD_UNLOAD:
		nlm_uninit();
		/* The NLM module cannot be safely unloaded. */
		/* FALLTHROUGH */
	default:
		return (EOPNOTSUPP);
	}
}