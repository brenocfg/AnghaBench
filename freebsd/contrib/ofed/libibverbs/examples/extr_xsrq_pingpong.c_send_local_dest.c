#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  union ibv_gid {int dummy; } ibv_gid ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  local_gid ;
typedef  int /*<<< orphan*/  gid ;
struct TYPE_8__ {scalar_t__ gidx; TYPE_3__* rem_dest; TYPE_2__** send_qp; TYPE_1__** recv_qp; int /*<<< orphan*/  lid; int /*<<< orphan*/  srq; int /*<<< orphan*/  ib_port; int /*<<< orphan*/  context; } ;
struct TYPE_7__ {int recv_psn; } ;
struct TYPE_6__ {int /*<<< orphan*/  qp_num; } ;
struct TYPE_5__ {int /*<<< orphan*/  qp_num; } ;

/* Variables and functions */
 char* ADDR_FORMAT ; 
 int /*<<< orphan*/  AF_INET6 ; 
 char* MSG_FORMAT ; 
 int MSG_SIZE ; 
 TYPE_4__ ctx ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  gid_to_wire_gid (union ibv_gid*,char*) ; 
 scalar_t__ ibv_get_srq_num (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ ibv_query_gid (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,union ibv_gid*) ; 
 int /*<<< orphan*/  inet_ntop (int /*<<< orphan*/ ,union ibv_gid*,char*,int) ; 
 int lrand48 () ; 
 int /*<<< orphan*/  memset (union ibv_gid*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 
 int write (int,char*,int) ; 

__attribute__((used)) static int send_local_dest(int sockfd, int index)
{
	char msg[MSG_SIZE];
	char gid[33];
	uint32_t srq_num;
	union ibv_gid local_gid;

	if (ctx.gidx >= 0) {
		if (ibv_query_gid(ctx.context, ctx.ib_port, ctx.gidx,
				  &local_gid)) {
			fprintf(stderr, "can't read sgid of index %d\n",
				ctx.gidx);
			return -1;
		}
	} else {
		memset(&local_gid, 0, sizeof(local_gid));
	}

	ctx.rem_dest[index].recv_psn = lrand48() & 0xffffff;
	if (ibv_get_srq_num(ctx.srq, &srq_num)) {
		fprintf(stderr, "Couldn't get SRQ num\n");
		return -1;
	}

	inet_ntop(AF_INET6, &local_gid, gid, sizeof(gid));
	printf(ADDR_FORMAT, "local", ctx.lid, ctx.recv_qp[index]->qp_num,
		ctx.send_qp[index]->qp_num, ctx.rem_dest[index].recv_psn,
		srq_num, gid);

	gid_to_wire_gid(&local_gid, gid);
	sprintf(msg, MSG_FORMAT, ctx.lid, ctx.recv_qp[index]->qp_num,
		ctx.send_qp[index]->qp_num, ctx.rem_dest[index].recv_psn,
		srq_num, gid);

	if (write(sockfd, msg, MSG_SIZE) != MSG_SIZE) {
		fprintf(stderr, "Couldn't send local address\n");
		return -1;
	}

	return 0;
}