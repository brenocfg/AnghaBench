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
struct iscsi_session_conf {char* isc_initiator; char* isc_target_addr; scalar_t__ isc_discovery; scalar_t__* isc_target; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISCSI_DEBUG (char*) ; 

__attribute__((used)) static bool
iscsi_valid_session_conf(const struct iscsi_session_conf *isc)
{

	if (isc->isc_initiator[0] == '\0') {
		ISCSI_DEBUG("empty isc_initiator");
		return (false);
	}

	if (isc->isc_target_addr[0] == '\0') {
		ISCSI_DEBUG("empty isc_target_addr");
		return (false);
	}

	if (isc->isc_discovery != 0 && isc->isc_target[0] != 0) {
		ISCSI_DEBUG("non-empty isc_target for discovery session");
		return (false);
	}

	if (isc->isc_discovery == 0 && isc->isc_target[0] == 0) {
		ISCSI_DEBUG("empty isc_target for non-discovery session");
		return (false);
	}

	return (true);
}