#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct ibmad_port {int dummy; } ;
typedef  int /*<<< orphan*/  ibmad_gid_t ;
struct TYPE_11__ {int /*<<< orphan*/  lid; int /*<<< orphan*/  drpath; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ ib_portid_t ;
typedef  enum MAD_DEST { ____Placeholder_MAD_DEST } MAD_DEST ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET6 ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  IBWARN (char*,int) ; 
#define  IB_DEST_DRPATH 132 
#define  IB_DEST_DRSLID 131 
#define  IB_DEST_GID 130 
#define  IB_DEST_GUID 129 
#define  IB_DEST_LID 128 
 int /*<<< orphan*/  IB_LID_VALID (int) ; 
 int /*<<< orphan*/  errno ; 
 int ib_portid_set (TYPE_1__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ib_resolve_gid_via (TYPE_1__*,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,struct ibmad_port const*) ; 
 int ib_resolve_guid_via (TYPE_1__*,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,struct ibmad_port const*) ; 
 int /*<<< orphan*/  ib_resolve_self_via (TYPE_1__*,int*,int /*<<< orphan*/ ,struct ibmad_port const*) ; 
 int /*<<< orphan*/  inet_pton (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  str2drpath (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int strtol (char*,char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strtoull (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int ib_resolve_portid_str_via(ib_portid_t * portid, char *addr_str,
			      enum MAD_DEST dest_type, ib_portid_t * sm_id,
			      const struct ibmad_port *srcport)
{
	ibmad_gid_t gid;
	uint64_t guid;
	int lid;
	char *routepath;
	ib_portid_t selfportid = { 0 };
	int selfport = 0;

	memset(portid, 0, sizeof *portid);

	switch (dest_type) {
	case IB_DEST_LID:
		lid = strtol(addr_str, 0, 0);
		if (!IB_LID_VALID(lid)) {
			errno = EINVAL;
			return -1;
		}
		return ib_portid_set(portid, lid, 0, 0);

	case IB_DEST_DRPATH:
		if (str2drpath(&portid->drpath, addr_str, 0, 0) < 0) {
			errno = EINVAL;
			return -1;
		}
		return 0;

	case IB_DEST_GUID:
		if (!(guid = strtoull(addr_str, 0, 0))) {
			errno = EINVAL;
			return -1;
		}

		/* keep guid in portid? */
		return ib_resolve_guid_via(portid, &guid, sm_id, 0, srcport);

	case IB_DEST_DRSLID:
		lid = strtol(addr_str, &routepath, 0);
		routepath++;
		if (!IB_LID_VALID(lid)) {
			errno = EINVAL;
			return -1;
		}
		ib_portid_set(portid, lid, 0, 0);

		/* handle DR parsing and set DrSLID to local lid */
		if (ib_resolve_self_via(&selfportid, &selfport, 0, srcport) < 0)
			return -1;
		if (str2drpath(&portid->drpath, routepath, selfportid.lid, 0) <
		    0) {
			errno = EINVAL;
			return -1;
		}
		return 0;

	case IB_DEST_GID:
		if (inet_pton(AF_INET6, addr_str, &gid) <= 0)
			return -1;
		return ib_resolve_gid_via(portid, gid, sm_id, 0, srcport);
	default:
		IBWARN("bad dest_type %d", dest_type);
		errno = EINVAL;
	}

	return -1;
}