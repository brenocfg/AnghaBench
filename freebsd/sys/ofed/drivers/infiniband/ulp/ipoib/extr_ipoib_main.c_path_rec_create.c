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
typedef  union ib_gid {int dummy; } ib_gid ;
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_5__ {int /*<<< orphan*/ * raw; } ;
struct TYPE_6__ {int numb_path; int /*<<< orphan*/  traffic_class; int /*<<< orphan*/  pkey; int /*<<< orphan*/  sgid; TYPE_1__ dgid; } ;
struct ipoib_path {TYPE_2__ pathrec; int /*<<< orphan*/  hwaddr; int /*<<< orphan*/  queue; struct ipoib_dev_priv* priv; } ;
struct ipoib_dev_priv {TYPE_4__* broadcast; int /*<<< orphan*/  pkey; int /*<<< orphan*/  local_gid; } ;
struct TYPE_7__ {int /*<<< orphan*/  traffic_class; } ;
struct TYPE_8__ {TYPE_3__ mcmember; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int INFINIBAND_ALEN ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  cpu_to_be16 (int /*<<< orphan*/ ) ; 
 struct ipoib_path* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static struct ipoib_path *
path_rec_create(struct ipoib_dev_priv *priv, uint8_t *hwaddr)
{
	struct ipoib_path *path;

	if (!priv->broadcast)
		return NULL;

	path = kzalloc(sizeof *path, GFP_ATOMIC);
	if (!path)
		return NULL;

	path->priv = priv;

	bzero(&path->queue, sizeof(path->queue));

#ifdef CONFIG_INFINIBAND_IPOIB_CM
	memcpy(&path->hwaddr, hwaddr, INFINIBAND_ALEN);
#endif
	memcpy(path->pathrec.dgid.raw, &hwaddr[4], sizeof (union ib_gid));
	path->pathrec.sgid	    = priv->local_gid;
	path->pathrec.pkey	    = cpu_to_be16(priv->pkey);
	path->pathrec.numb_path     = 1;
	path->pathrec.traffic_class = priv->broadcast->mcmember.traffic_class;

	return path;
}