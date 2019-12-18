#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sysctl_oid {int dummy; } ;
typedef  TYPE_1__* linker_file_t ;
struct TYPE_4__ {int /*<<< orphan*/  filename; } ;

/* Variables and functions */
 int /*<<< orphan*/  FILE ; 
 int /*<<< orphan*/  KLD_DPF (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SA_XLOCKED ; 
 int /*<<< orphan*/  kld_sx ; 
 scalar_t__ linker_file_lookup_set (TYPE_1__*,char*,struct sysctl_oid***,struct sysctl_oid***,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysctl_register_disabled_oid (struct sysctl_oid*) ; 
 int /*<<< orphan*/  sysctl_register_oid (struct sysctl_oid*) ; 
 int /*<<< orphan*/  sysctl_wlock () ; 
 int /*<<< orphan*/  sysctl_wunlock () ; 

__attribute__((used)) static void
linker_file_register_sysctls(linker_file_t lf, bool enable)
{
	struct sysctl_oid **start, **stop, **oidp;

	KLD_DPF(FILE,
	    ("linker_file_register_sysctls: registering SYSCTLs for %s\n",
	    lf->filename));

	sx_assert(&kld_sx, SA_XLOCKED);

	if (linker_file_lookup_set(lf, "sysctl_set", &start, &stop, NULL) != 0)
		return;

	sx_xunlock(&kld_sx);
	sysctl_wlock();
	for (oidp = start; oidp < stop; oidp++) {
		if (enable)
			sysctl_register_oid(*oidp);
		else
			sysctl_register_disabled_oid(*oidp);
	}
	sysctl_wunlock();
	sx_xlock(&kld_sx);
}