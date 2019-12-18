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
struct TYPE_2__ {int /*<<< orphan*/  method; } ;
struct ib_sa_mad {TYPE_1__ mad_hdr; } ;
struct mcast_req {struct ib_sa_mad sa_mad; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB_SA_METHOD_DELETE ; 

__attribute__((used)) static void build_leave_mad(struct mcast_req *req)
{
	struct ib_sa_mad *mad = &req->sa_mad;

	mad->mad_hdr.method = IB_SA_METHOD_DELETE;
}