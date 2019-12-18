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
struct TYPE_2__ {int sl; void* qkey; int /*<<< orphan*/  lid; void* qpn; } ;
struct ib_user_mad {TYPE_1__ addr; } ;
typedef  void* __be32 ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be16toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be32toh (void*) ; 

int umad_set_addr_net(void *umad, __be16 dlid, __be32 dqp, int sl, __be32 qkey)
{
	struct ib_user_mad *mad = umad;

	TRACE("umad %p dlid %u dqp %d sl %d qkey %x",
	      umad, be16toh(dlid), be32toh(dqp), sl, be32toh(qkey));
	mad->addr.qpn = dqp;
	mad->addr.lid = dlid;
	mad->addr.qkey = qkey;
	mad->addr.sl = sl;

	return 0;
}