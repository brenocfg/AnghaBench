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
 int /*<<< orphan*/  INT_MAX ; 
#define  MOD_LOAD 129 
#define  MOD_UNLOAD 128 
 int /*<<< orphan*/  new_unrhdr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ueunit ; 

__attribute__((used)) static int
uether_modevent(module_t mod, int type, void *data)
{

	switch (type) {
	case MOD_LOAD:
		ueunit = new_unrhdr(0, INT_MAX, NULL);
		break;
	case MOD_UNLOAD:
		break;
	default:
		return (EOPNOTSUPP);
	}
	return (0);
}