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
struct TYPE_4__ {int /*<<< orphan*/ ** chains; } ;
typedef  TYPE_1__ pam_handle_t ;
typedef  size_t pam_facility_t ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  ENTERS (char const*) ; 
 int /*<<< orphan*/  FALLBACK_TO_OTHER ; 
 scalar_t__ OPENPAM_FEATURE (int /*<<< orphan*/ ) ; 
 size_t PAM_FACILITY_ANY ; 
 int /*<<< orphan*/  PAM_LOG_ERROR ; 
 size_t PAM_NUM_FACILITIES ; 
 char const* PAM_OTHER ; 
 int /*<<< orphan*/  PAM_SUCCESS ; 
 int /*<<< orphan*/  PAM_SYSTEM_ERR ; 
 int /*<<< orphan*/  RETURNC (int /*<<< orphan*/ ) ; 
 int errno ; 
 int /*<<< orphan*/  openpam_clear_chains (int /*<<< orphan*/ **) ; 
 scalar_t__ openpam_load_chain (TYPE_1__*,char const*,size_t) ; 
 int /*<<< orphan*/  openpam_log (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  valid_service_name (char const*) ; 

int
openpam_configure(pam_handle_t *pamh,
	const char *service)
{
	pam_facility_t fclt;
	int serrno;

	ENTERS(service);
	if (!valid_service_name(service)) {
		openpam_log(PAM_LOG_ERROR, "invalid service name");
		RETURNC(PAM_SYSTEM_ERR);
	}
	if (openpam_load_chain(pamh, service, PAM_FACILITY_ANY) < 0) {
		if (errno != ENOENT)
			goto load_err;
	}
	for (fclt = 0; fclt < PAM_NUM_FACILITIES; ++fclt) {
		if (pamh->chains[fclt] != NULL)
			continue;
		if (OPENPAM_FEATURE(FALLBACK_TO_OTHER)) {
			if (openpam_load_chain(pamh, PAM_OTHER, fclt) < 0)
				goto load_err;
		}
	}
	RETURNC(PAM_SUCCESS);
load_err:
	serrno = errno;
	openpam_clear_chains(pamh->chains);
	errno = serrno;
	RETURNC(PAM_SYSTEM_ERR);
}