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
typedef  int /*<<< orphan*/  uint8_t ;
struct ib_user_mad_reg_req {int qpn; int mgmt_class; int mgmt_class_version; int id; int /*<<< orphan*/  oui; int /*<<< orphan*/ * method_mask; int /*<<< orphan*/  rmpp_version; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG (char*,int,int,int,...) ; 
 int EPERM ; 
 int /*<<< orphan*/  IB_OPENIB_OUI ; 
 int /*<<< orphan*/  IB_USER_MAD_REGISTER_AGENT ; 
 int /*<<< orphan*/  TRACE (char*,int,int,int,int /*<<< orphan*/ ,long*) ; 
 int /*<<< orphan*/  VALGRIND_MAKE_MEM_DEFINED (struct ib_user_mad_reg_req*,int) ; 
 int /*<<< orphan*/  htobe32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ioctl (int,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,...) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

int umad_register(int fd, int mgmt_class, int mgmt_version,
		  uint8_t rmpp_version, long method_mask[])
{
	struct ib_user_mad_reg_req req;
	__be32 oui = htobe32(IB_OPENIB_OUI);
	int qp;

	TRACE
	    ("fd %d mgmt_class %u mgmt_version %u rmpp_version %d method_mask %p",
	     fd, mgmt_class, mgmt_version, rmpp_version, method_mask);

	req.qpn = qp = (mgmt_class == 0x1 || mgmt_class == 0x81) ? 0 : 1;
	req.mgmt_class = mgmt_class;
	req.mgmt_class_version = mgmt_version;
	req.rmpp_version = rmpp_version;

	if (method_mask)
		memcpy(req.method_mask, method_mask, sizeof req.method_mask);
	else
		memset(req.method_mask, 0, sizeof req.method_mask);

	memcpy(&req.oui, (char *)&oui + 1, sizeof req.oui);

	VALGRIND_MAKE_MEM_DEFINED(&req, sizeof req);

	if (!ioctl(fd, IB_USER_MAD_REGISTER_AGENT, (void *)&req)) {
		DEBUG("fd %d registered to use agent %d qp %d", fd, req.id, qp);
		return req.id;	/* return agentid */
	}

	DEBUG("fd %d registering qp %d class 0x%x version %d failed: %m",
	      fd, qp, mgmt_class, mgmt_version);
	return -EPERM;
}