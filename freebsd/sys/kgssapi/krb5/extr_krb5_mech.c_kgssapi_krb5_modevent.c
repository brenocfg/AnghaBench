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
#define  MOD_LOAD 129 
#define  MOD_UNLOAD 128 
 int /*<<< orphan*/  kgss_install_mech (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kgss_uninstall_mech (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_class ; 
 int /*<<< orphan*/  krb5_mech_oid ; 

__attribute__((used)) static int
kgssapi_krb5_modevent(module_t mod, int type, void *data)
{

	switch (type) {
	case MOD_LOAD:
		kgss_install_mech(&krb5_mech_oid, "kerberosv5", &krb5_class);
		break;

	case MOD_UNLOAD:
		kgss_uninstall_mech(&krb5_mech_oid);
		break;
	}


	return (0);
}