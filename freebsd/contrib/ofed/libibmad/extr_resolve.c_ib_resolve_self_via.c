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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint64_t ;
struct ibmad_port {int dummy; } ;
typedef  int /*<<< orphan*/  ibmad_gid_t ;
struct TYPE_4__ {int lid; int sl; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ ib_portid_t ;

/* Variables and functions */
 int /*<<< orphan*/  IB_ATTR_NODE_INFO ; 
 int /*<<< orphan*/  IB_ATTR_PORT_INFO ; 
 int /*<<< orphan*/  IB_GID_GUID_F ; 
 int /*<<< orphan*/  IB_GID_PREFIX_F ; 
 int /*<<< orphan*/  IB_NODE_LOCAL_PORT_F ; 
 int /*<<< orphan*/  IB_NODE_PORT_GUID_F ; 
 int /*<<< orphan*/  IB_PORT_GID_PREFIX_F ; 
 int /*<<< orphan*/  IB_PORT_LID_F ; 
 int /*<<< orphan*/  IB_PORT_SMSL_F ; 
 int /*<<< orphan*/  mad_decode_field (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  mad_encode_field (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  smp_query_via (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ibmad_port const*) ; 

int ib_resolve_self_via(ib_portid_t * portid, int *portnum, ibmad_gid_t * gid,
			const struct ibmad_port *srcport)
{
	ib_portid_t self = { 0 };
	uint8_t portinfo[64];
	uint8_t nodeinfo[64];
	uint64_t guid, prefix;

	if (!smp_query_via(nodeinfo, &self, IB_ATTR_NODE_INFO, 0, 0, srcport))
		return -1;

	if (!smp_query_via(portinfo, &self, IB_ATTR_PORT_INFO, 0, 0, srcport))
		return -1;

	mad_decode_field(portinfo, IB_PORT_LID_F, &portid->lid);
	mad_decode_field(portinfo, IB_PORT_SMSL_F, &portid->sl);
	mad_decode_field(portinfo, IB_PORT_GID_PREFIX_F, &prefix);
	mad_decode_field(nodeinfo, IB_NODE_PORT_GUID_F, &guid);

	if (portnum)
		mad_decode_field(nodeinfo, IB_NODE_LOCAL_PORT_F, portnum);
	if (gid) {
		mad_encode_field(*gid, IB_GID_PREFIX_F, &prefix);
		mad_encode_field(*gid, IB_GID_GUID_F, &guid);
	}
	return 0;
}