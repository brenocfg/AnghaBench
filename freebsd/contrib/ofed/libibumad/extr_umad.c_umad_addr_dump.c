#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int* gid; int /*<<< orphan*/  pkey_index; int /*<<< orphan*/  flow_label; scalar_t__ traffic_class; scalar_t__ hop_limit; scalar_t__ gid_index; int /*<<< orphan*/  grh_present; int /*<<< orphan*/  sl; int /*<<< orphan*/  lid; int /*<<< orphan*/  qkey; int /*<<< orphan*/  qpn; } ;
typedef  TYPE_1__ ib_mad_addr_t ;

/* Variables and functions */
 char HEX (int) ; 
 int /*<<< orphan*/  IBWARN (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  be16toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be32toh (int /*<<< orphan*/ ) ; 

void umad_addr_dump(ib_mad_addr_t * addr)
{
#define HEX(x)  ((x) < 10 ? '0' + (x) : 'a' + ((x) -10))
	char gid_str[64];
	int i;

	for (i = 0; i < sizeof addr->gid; i++) {
		gid_str[i * 2] = HEX(addr->gid[i] >> 4);
		gid_str[i * 2 + 1] = HEX(addr->gid[i] & 0xf);
	}
	gid_str[i * 2] = 0;
	IBWARN("qpn %d qkey 0x%x lid %u sl %d\n"
	       "grh_present %d gid_index %d hop_limit %d traffic_class %d flow_label 0x%x pkey_index 0x%x\n"
	       "Gid 0x%s",
	       be32toh(addr->qpn), be32toh(addr->qkey), be16toh(addr->lid), addr->sl,
	       addr->grh_present, (int)addr->gid_index, (int)addr->hop_limit,
	       (int)addr->traffic_class, addr->flow_label, addr->pkey_index,
	       gid_str);
}