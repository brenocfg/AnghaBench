#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct dumperinfo {TYPE_1__* kdcrypto; TYPE_2__* kdcomp; int /*<<< orphan*/  di_devname; } ;
struct diocskerneldump_arg {scalar_t__ kda_index; scalar_t__ kda_compression; scalar_t__ kda_encryption; } ;
struct TYPE_4__ {scalar_t__ kdc_format; } ;
struct TYPE_3__ {scalar_t__ kdc_encryption; } ;

/* Variables and functions */
 scalar_t__ KDA_REMOVE_ALL ; 
 scalar_t__ KDA_REMOVE_DEV ; 
 scalar_t__ KERNELDUMP_COMP_NONE ; 
 scalar_t__ KERNELDUMP_ENC_NONE ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static bool
dumper_config_match(const struct dumperinfo *di, const char *devname,
    const struct diocskerneldump_arg *kda)
{
	if (kda->kda_index == KDA_REMOVE_ALL)
		return (true);

	if (strcmp(di->di_devname, devname) != 0)
		return (false);

	/*
	 * Allow wildcard removal of configs matching a device on g_dev_orphan.
	 */
	if (kda->kda_index == KDA_REMOVE_DEV)
		return (true);

	if (di->kdcomp != NULL) {
		if (di->kdcomp->kdc_format != kda->kda_compression)
			return (false);
	} else if (kda->kda_compression != KERNELDUMP_COMP_NONE)
		return (false);
#ifdef EKCD
	if (di->kdcrypto != NULL) {
		if (di->kdcrypto->kdc_encryption != kda->kda_encryption)
			return (false);
		/*
		 * Do we care to verify keys match to delete?  It seems weird
		 * to expect multiple fallback dump configurations on the same
		 * device that only differ in crypto key.
		 */
	} else
#endif
		if (kda->kda_encryption != KERNELDUMP_ENC_NONE)
			return (false);

	return (true);
}