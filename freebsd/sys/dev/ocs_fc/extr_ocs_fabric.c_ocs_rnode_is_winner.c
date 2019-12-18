#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  long long uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  prop_buf ;
struct TYPE_7__ {long long wwpn; int /*<<< orphan*/  ocs; TYPE_1__* domain; } ;
typedef  TYPE_2__ ocs_sport_t ;
typedef  int int32_t ;
struct TYPE_8__ {int /*<<< orphan*/  port_name_lo; int /*<<< orphan*/  port_name_hi; } ;
typedef  TYPE_3__ fc_plogi_payload_t ;
struct TYPE_6__ {scalar_t__ flogi_service_params; } ;

/* Variables and functions */
 int /*<<< orphan*/  ocs_be32toh (int /*<<< orphan*/ ) ; 
 scalar_t__ ocs_get_property (char*,char*,int) ; 
 long long ocs_get_wwpn (TYPE_3__*) ; 
 int /*<<< orphan*/  ocs_log_debug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_log_warn (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 long long ocs_strtoull (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int32_t
ocs_rnode_is_winner(ocs_sport_t *sport)
{
	fc_plogi_payload_t *remote_sparms = (fc_plogi_payload_t*) sport->domain->flogi_service_params;
	uint64_t remote_wwpn = ocs_get_wwpn(remote_sparms);
	uint64_t local_wwpn = sport->wwpn;
	char prop_buf[32];
	uint64_t wwn_bump = 0;

	if (ocs_get_property("wwn_bump", prop_buf, sizeof(prop_buf)) == 0) {
		wwn_bump = ocs_strtoull(prop_buf, 0, 0);
	}
	local_wwpn ^= wwn_bump;

	remote_wwpn = ocs_get_wwpn(remote_sparms);

	ocs_log_debug(sport->ocs, "r: %08x %08x\n", ocs_be32toh(remote_sparms->port_name_hi), ocs_be32toh(remote_sparms->port_name_lo));
	ocs_log_debug(sport->ocs, "l: %08x %08x\n", (uint32_t) (local_wwpn >> 32ll), (uint32_t) local_wwpn);

	if (remote_wwpn == local_wwpn) {
		ocs_log_warn(sport->ocs, "WWPN of remote node [%08x %08x] matches local WWPN\n",
			(uint32_t) (local_wwpn >> 32ll), (uint32_t) local_wwpn);
		return (-1);
	}

	return (remote_wwpn > local_wwpn);
}