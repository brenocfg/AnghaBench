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
 int EINVAL ; 
#define  MOD_LOAD 129 
#define  MOD_UNLOAD 128 
 int /*<<< orphan*/  init_crypto_tkip_test () ; 

__attribute__((used)) static int
test_tkip_modevent(module_t mod, int type, void *unused)
{
	switch (type) {
	case MOD_LOAD:
		(void) init_crypto_tkip_test();
		return 0;
	case MOD_UNLOAD:
		return 0;
	}
	return EINVAL;
}