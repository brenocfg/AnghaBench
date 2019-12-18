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
struct consdev {int /*<<< orphan*/  cn_pri; int /*<<< orphan*/  cn_name; } ;

/* Variables and functions */
 scalar_t__ BVM_CONS_SIG ; 
 int /*<<< orphan*/  CN_DEAD ; 
 int /*<<< orphan*/  CN_REMOTE ; 
 int bvm_cons_port ; 
 scalar_t__ inw (int) ; 
 scalar_t__ resource_int_value (char*,int /*<<< orphan*/ ,char*,int*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
bvm_cnprobe(struct consdev *cp)
{
	int disabled, port;

	disabled = 0;
	cp->cn_pri = CN_DEAD;
	strcpy(cp->cn_name, "bvmcons");

	resource_int_value("bvmconsole", 0, "disabled", &disabled);
	if (!disabled) {
		if (resource_int_value("bvmconsole", 0, "port", &port) == 0)
			bvm_cons_port = port;

		if (inw(bvm_cons_port) == BVM_CONS_SIG)
			cp->cn_pri = CN_REMOTE;
	}
}