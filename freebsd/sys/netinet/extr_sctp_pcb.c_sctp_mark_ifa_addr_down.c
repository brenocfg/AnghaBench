#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  char const* uint32_t ;
struct sockaddr {int dummy; } ;
struct sctp_vrf {int /*<<< orphan*/  vrf_id; } ;
struct sctp_ifa {int /*<<< orphan*/  localifa_flags; TYPE_1__* ifn_p; } ;
struct TYPE_2__ {char const* ifn_name; char const* ifn_index; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCTPDBG (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  SCTP_ADDR_IFA_UNUSEABLE ; 
 int /*<<< orphan*/  SCTP_ADDR_LOCKED ; 
 int /*<<< orphan*/  SCTP_ADDR_VALID ; 
 int /*<<< orphan*/  SCTP_DEBUG_PCB4 ; 
 int /*<<< orphan*/  SCTP_IFNAMSIZ ; 
 int /*<<< orphan*/  SCTP_IPI_ADDR_RLOCK () ; 
 int /*<<< orphan*/  SCTP_IPI_ADDR_RUNLOCK () ; 
 struct sctp_ifa* sctp_find_ifa_by_addr (struct sockaddr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sctp_vrf* sctp_find_vrf (char const*) ; 
 scalar_t__ strncmp (char const*,char const*,int /*<<< orphan*/ ) ; 

void
sctp_mark_ifa_addr_down(uint32_t vrf_id, struct sockaddr *addr,
    const char *if_name, uint32_t ifn_index)
{
	struct sctp_vrf *vrf;
	struct sctp_ifa *sctp_ifap;

	SCTP_IPI_ADDR_RLOCK();
	vrf = sctp_find_vrf(vrf_id);
	if (vrf == NULL) {
		SCTPDBG(SCTP_DEBUG_PCB4, "Can't find vrf_id 0x%x\n", vrf_id);
		goto out;

	}
	sctp_ifap = sctp_find_ifa_by_addr(addr, vrf->vrf_id, SCTP_ADDR_LOCKED);
	if (sctp_ifap == NULL) {
		SCTPDBG(SCTP_DEBUG_PCB4, "Can't find sctp_ifap for address\n");
		goto out;
	}
	if (sctp_ifap->ifn_p == NULL) {
		SCTPDBG(SCTP_DEBUG_PCB4, "IFA has no IFN - can't mark unusable\n");
		goto out;
	}
	if (if_name) {
		if (strncmp(if_name, sctp_ifap->ifn_p->ifn_name, SCTP_IFNAMSIZ) != 0) {
			SCTPDBG(SCTP_DEBUG_PCB4, "IFN %s of IFA not the same as %s\n",
			    sctp_ifap->ifn_p->ifn_name, if_name);
			goto out;
		}
	} else {
		if (sctp_ifap->ifn_p->ifn_index != ifn_index) {
			SCTPDBG(SCTP_DEBUG_PCB4, "IFA owned by ifn_index:%d down command for ifn_index:%d - ignored\n",
			    sctp_ifap->ifn_p->ifn_index, ifn_index);
			goto out;
		}
	}

	sctp_ifap->localifa_flags &= (~SCTP_ADDR_VALID);
	sctp_ifap->localifa_flags |= SCTP_ADDR_IFA_UNUSEABLE;
out:
	SCTP_IPI_ADDR_RUNLOCK();
}