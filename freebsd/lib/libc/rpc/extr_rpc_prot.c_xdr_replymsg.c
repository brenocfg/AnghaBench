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
struct TYPE_2__ {int rp_stat; int /*<<< orphan*/  ru; } ;
struct rpc_msg {int rm_direction; TYPE_1__ rm_reply; int /*<<< orphan*/  rm_xid; } ;
typedef  int /*<<< orphan*/  enum_t ;
typedef  enum reply_stat { ____Placeholder_reply_stat } reply_stat ;
typedef  enum msg_type { ____Placeholder_msg_type } msg_type ;
typedef  int /*<<< orphan*/  caddr_t ;
typedef  int /*<<< orphan*/  bool_t ;
typedef  int /*<<< orphan*/  XDR ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  NULL_xdrproc_t ; 
 scalar_t__ REPLY ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reply_dscrm ; 
 scalar_t__ xdr_enum (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ xdr_u_int32_t (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xdr_union (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool_t
xdr_replymsg(XDR *xdrs, struct rpc_msg *rmsg)
{
	enum msg_type *prm_direction;
	enum reply_stat *prp_stat;

	assert(xdrs != NULL);
	assert(rmsg != NULL);

	prm_direction = &rmsg->rm_direction;
	prp_stat = &rmsg->rm_reply.rp_stat;

	if (
	    xdr_u_int32_t(xdrs, &(rmsg->rm_xid)) && 
	    xdr_enum(xdrs, (enum_t *) prm_direction) &&
	    (rmsg->rm_direction == REPLY) )
		return (xdr_union(xdrs, (enum_t *) prp_stat,
		   (caddr_t)(void *)&(rmsg->rm_reply.ru), reply_dscrm,
		   NULL_xdrproc_t));
	return (FALSE);
}