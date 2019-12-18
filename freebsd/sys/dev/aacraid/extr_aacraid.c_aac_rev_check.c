#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct aac_softc {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  dash; int /*<<< orphan*/  type; int /*<<< orphan*/  minor; int /*<<< orphan*/  major; } ;
struct TYPE_7__ {TYPE_2__ comp; } ;
struct TYPE_8__ {int /*<<< orphan*/  buildNumber; TYPE_3__ external; } ;
struct aac_rev_check_resp {int possiblyCompatible; TYPE_4__ adapterSWRevision; } ;
struct TYPE_5__ {int /*<<< orphan*/  buildNumber; } ;
struct aac_rev_check {TYPE_1__ callingRevision; } ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  AAC_DRIVER_BUGFIX_LEVEL ; 
 int /*<<< orphan*/  AAC_DRIVER_BUILD ; 
 int /*<<< orphan*/  AAC_DRIVER_MAJOR_VERSION ; 
 int /*<<< orphan*/  AAC_DRIVER_MINOR_VERSION ; 
 int /*<<< orphan*/  AAC_DRIVER_TYPE ; 
 char* HBA_FLAGS_DBG_FUNCTION_ENTRY_B ; 
 char* HBA_FLAGS_DBG_IOCTL_COMMANDS_B ; 
 int copyin (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int copyout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fwprintf (struct aac_softc*,char*,char*,...) ; 

__attribute__((used)) static int
aac_rev_check(struct aac_softc *sc, caddr_t udata)
{
	struct aac_rev_check rev_check;
	struct aac_rev_check_resp rev_check_resp;
	int error = 0;

	fwprintf(sc, HBA_FLAGS_DBG_FUNCTION_ENTRY_B, "");

	/*
	 * Copyin the revision struct from userspace
	 */
	if ((error = copyin(udata, (caddr_t)&rev_check,
			sizeof(struct aac_rev_check))) != 0) {
		return error;
	}

	fwprintf(sc, HBA_FLAGS_DBG_IOCTL_COMMANDS_B, "Userland revision= %d\n",
	      rev_check.callingRevision.buildNumber);

	/*
	 * Doctor up the response struct.
	 */
	rev_check_resp.possiblyCompatible = 1;
	rev_check_resp.adapterSWRevision.external.comp.major =
	    AAC_DRIVER_MAJOR_VERSION;
	rev_check_resp.adapterSWRevision.external.comp.minor =
	    AAC_DRIVER_MINOR_VERSION;
	rev_check_resp.adapterSWRevision.external.comp.type =
	    AAC_DRIVER_TYPE;
	rev_check_resp.adapterSWRevision.external.comp.dash =
	    AAC_DRIVER_BUGFIX_LEVEL;
	rev_check_resp.adapterSWRevision.buildNumber =
	    AAC_DRIVER_BUILD;

	return(copyout((caddr_t)&rev_check_resp, udata,
			sizeof(struct aac_rev_check_resp)));
}