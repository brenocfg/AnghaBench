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
struct priv {int /*<<< orphan*/  sscop; } ;
struct ngm_queue_state {int dummy; } ;
struct TYPE_2__ {int arglen; int cmd; } ;
struct ng_mesg {TYPE_1__ header; } ;
typedef  int /*<<< orphan*/  node_p ;

/* Variables and functions */
 int EINVAL ; 
#define  NGM_HIGH_WATER_PASSED 129 
#define  NGM_LOW_WATER_PASSED 128 
 struct priv* NG_NODE_PRIVATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sscop_setbusy (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
flow_lower(node_p node, struct ng_mesg *msg)
{
	struct priv *priv = NG_NODE_PRIVATE(node);

	if (msg->header.arglen != sizeof(struct ngm_queue_state))
		return (EINVAL);

	switch (msg->header.cmd) {

	  case NGM_HIGH_WATER_PASSED:
		sscop_setbusy(priv->sscop, 1);
		break;

	  case NGM_LOW_WATER_PASSED:
		sscop_setbusy(priv->sscop, 1);
		break;

	  default:
		return (EINVAL);
	}
	return (0);
}