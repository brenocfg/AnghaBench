#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int type; } ;
struct pf_rule_addr {TYPE_4__ addr; } ;
struct TYPE_8__ {int /*<<< orphan*/  addr32; } ;
struct TYPE_7__ {int /*<<< orphan*/  addr32; } ;
struct TYPE_9__ {TYPE_2__ mask; TYPE_1__ addr; } ;
struct TYPE_11__ {TYPE_3__ a; int /*<<< orphan*/  tblname; int /*<<< orphan*/  ifname; } ;
struct TYPE_12__ {TYPE_5__ v; int /*<<< orphan*/  iflags; int /*<<< orphan*/  type; } ;
typedef  int /*<<< orphan*/  MD5_CTX ;

/* Variables and functions */
#define  PF_ADDR_ADDRMASK 130 
#define  PF_ADDR_DYNIFTL 129 
#define  PF_ADDR_TABLE 128 
 int /*<<< orphan*/  PF_MD5_UPD (struct pf_rule_addr*,int /*<<< orphan*/ ) ; 
 TYPE_6__ addr ; 
 int /*<<< orphan*/  neg ; 
 int /*<<< orphan*/ * port ; 
 int /*<<< orphan*/  port_op ; 

__attribute__((used)) static void
pf_hash_rule_addr(MD5_CTX *ctx, struct pf_rule_addr *pfr)
{
	PF_MD5_UPD(pfr, addr.type);
	switch (pfr->addr.type) {
		case PF_ADDR_DYNIFTL:
			PF_MD5_UPD(pfr, addr.v.ifname);
			PF_MD5_UPD(pfr, addr.iflags);
			break;
		case PF_ADDR_TABLE:
			PF_MD5_UPD(pfr, addr.v.tblname);
			break;
		case PF_ADDR_ADDRMASK:
			/* XXX ignore af? */
			PF_MD5_UPD(pfr, addr.v.a.addr.addr32);
			PF_MD5_UPD(pfr, addr.v.a.mask.addr32);
			break;
	}

	PF_MD5_UPD(pfr, port[0]);
	PF_MD5_UPD(pfr, port[1]);
	PF_MD5_UPD(pfr, neg);
	PF_MD5_UPD(pfr, port_op);
}