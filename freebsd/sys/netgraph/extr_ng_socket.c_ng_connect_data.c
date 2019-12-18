#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct sockaddr_ng {int /*<<< orphan*/  sg_data; } ;
struct sockaddr {int dummy; } ;
struct ngsock {int /*<<< orphan*/  mtx; int /*<<< orphan*/  refs; TYPE_2__* node; struct ngpcb* datasock; } ;
struct ngpcb {int /*<<< orphan*/  node_id; struct ngsock* sockdata; } ;
typedef  TYPE_3__* node_p ;
typedef  TYPE_4__* item_p ;
struct TYPE_12__ {TYPE_3__* el_dest; } ;
struct TYPE_11__ {TYPE_1__* nd_type; } ;
struct TYPE_10__ {int /*<<< orphan*/  nd_ID; } ;
struct TYPE_9__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EADDRINUSE ; 
 int EINVAL ; 
 int EISCONN ; 
 int /*<<< orphan*/  NG_FREE_ITEM (TYPE_4__*) ; 
 struct ngsock* NG_NODE_PRIVATE (TYPE_3__*) ; 
 int /*<<< orphan*/  NG_SOCKET_NODE_TYPE ; 
 int /*<<< orphan*/  NG_WAITOK ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int ng_address_path (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__* ng_package_data (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ng_connect_data(struct sockaddr *nam, struct ngpcb *pcbp)
{
	struct sockaddr_ng *sap;
	node_p farnode;
	struct ngsock *priv;
	int error;
	item_p item;

	/* If we are already connected, don't do it again. */
	if (pcbp->sockdata != NULL)
		return (EISCONN);

	/*
	 * Find the target (victim) and check it doesn't already have
	 * a data socket. Also check it is a 'socket' type node.
	 * Use ng_package_data() and ng_address_path() to do this.
	 */

	sap = (struct sockaddr_ng *) nam;
	/* The item will hold the node reference. */
	item = ng_package_data(NULL, NG_WAITOK);

	if ((error = ng_address_path(NULL, item,  sap->sg_data, 0)))
		return (error); /* item is freed on failure */

	/*
	 * Extract node from item and free item. Remember we now have
	 * a reference on the node. The item holds it for us.
	 * when we free the item we release the reference.
	 */
	farnode = item->el_dest; /* shortcut */
	if (strcmp(farnode->nd_type->name, NG_SOCKET_NODE_TYPE) != 0) {
		NG_FREE_ITEM(item); /* drop the reference to the node */
		return (EINVAL);
	}
	priv = NG_NODE_PRIVATE(farnode);
	if (priv->datasock != NULL) {
		NG_FREE_ITEM(item);	/* drop the reference to the node */
		return (EADDRINUSE);
	}

	/*
	 * Link the PCB and the private data struct. and note the extra
	 * reference. Drop the extra reference on the node.
	 */
	mtx_lock(&priv->mtx);
	priv->datasock = pcbp;
	pcbp->sockdata = priv;
	pcbp->node_id = priv->node->nd_ID;	/* hint for netstat(1) */
	priv->refs++;
	mtx_unlock(&priv->mtx);
	NG_FREE_ITEM(item);	/* drop the reference to the node */
	return (0);
}