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
struct socket {int dummy; } ;
struct sockaddr_ng {int sg_len; int /*<<< orphan*/  sg_family; int /*<<< orphan*/  sg_data; } ;
struct sockaddr {int dummy; } ;
struct ngpcb {TYPE_1__* sockdata; } ;
typedef  int /*<<< orphan*/ * node_p ;
struct TYPE_2__ {int /*<<< orphan*/  mtx; int /*<<< orphan*/ * node; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_NETGRAPH ; 
 int EINVAL ; 
 int /*<<< orphan*/  M_SONAME ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int NG_NODESIZ ; 
 scalar_t__ NG_NODE_HAS_NAME (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NG_NODE_NAME (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct sockaddr_ng*,int /*<<< orphan*/ ) ; 
 struct sockaddr_ng* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 struct ngpcb* sotongpcb (struct socket*) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ng_getsockaddr(struct socket *so, struct sockaddr **addr)
{
	struct ngpcb *pcbp;
	struct sockaddr_ng *sg;
	int sg_len;
	int error = 0;

	pcbp = sotongpcb(so);
	if ((pcbp == NULL) || (pcbp->sockdata == NULL))
		/* XXXGL: can this still happen? */
		return (EINVAL);

	sg_len = sizeof(struct sockaddr_ng) + NG_NODESIZ -
	    sizeof(sg->sg_data);
	sg = malloc(sg_len, M_SONAME, M_WAITOK | M_ZERO);

	mtx_lock(&pcbp->sockdata->mtx);
	if (pcbp->sockdata->node != NULL) {
		node_p node = pcbp->sockdata->node;

		if (NG_NODE_HAS_NAME(node))
			bcopy(NG_NODE_NAME(node), sg->sg_data,
			    strlen(NG_NODE_NAME(node)));
		mtx_unlock(&pcbp->sockdata->mtx);

		sg->sg_len = sg_len;
		sg->sg_family = AF_NETGRAPH;
		*addr = (struct sockaddr *)sg;
	} else {
		mtx_unlock(&pcbp->sockdata->mtx);
		free(sg, M_SONAME);
		error = EINVAL;
	}

	return (error);
}