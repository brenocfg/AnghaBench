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

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*,void*,int,int,int,int) ; 
 int /*<<< orphan*/  htobe16 (int) ; 
 void* htobe32 (int) ; 

int umad_set_addr(void *umad, int dlid, int dqp, int sl, int qkey)
{
	struct ib_user_mad *mad = umad;

	TRACE("umad %p dlid %u dqp %d sl %d, qkey %x",
	      umad, dlid, dqp, sl, qkey);
	mad->addr.qpn = htobe32(dqp);
	mad->addr.lid = htobe16(dlid);
	mad->addr.qkey = htobe32(qkey);
	mad->addr.sl = sl;

	return 0;
}