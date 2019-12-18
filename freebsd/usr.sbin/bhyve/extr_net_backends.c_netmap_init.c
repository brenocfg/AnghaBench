#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct netmap_priv {char* ifname; int /*<<< orphan*/ * mevp; TYPE_2__* nmd; void* cb_param; int /*<<< orphan*/  cb; int /*<<< orphan*/  rx; int /*<<< orphan*/  tx; int /*<<< orphan*/  memid; } ;
struct net_backend {int /*<<< orphan*/  fd; scalar_t__ opaque; } ;
typedef  int /*<<< orphan*/  net_be_rxeof_t ;
struct TYPE_3__ {int /*<<< orphan*/  nr_arg2; } ;
struct TYPE_4__ {int /*<<< orphan*/  fd; int /*<<< orphan*/  nifp; TYPE_1__ req; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVF_READ ; 
 int /*<<< orphan*/  NETMAP_NO_TX_POLL ; 
 int /*<<< orphan*/  NETMAP_RXRING (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NETMAP_TXRING (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WPRINTF (char*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (struct netmap_priv*) ; 
 int /*<<< orphan*/ * mevent_add_disabled (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 TYPE_2__* nm_open (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,int) ; 

__attribute__((used)) static int
netmap_init(struct net_backend *be, const char *devname,
	    net_be_rxeof_t cb, void *param)
{
	struct netmap_priv *priv = (struct netmap_priv *)be->opaque;

	strlcpy(priv->ifname, devname, sizeof(priv->ifname));
	priv->ifname[sizeof(priv->ifname) - 1] = '\0';

	priv->nmd = nm_open(priv->ifname, NULL, NETMAP_NO_TX_POLL, NULL);
	if (priv->nmd == NULL) {
		WPRINTF(("Unable to nm_open(): interface '%s', errno (%s)\n",
			devname, strerror(errno)));
		free(priv);
		return (-1);
	}

	priv->memid = priv->nmd->req.nr_arg2;
	priv->tx = NETMAP_TXRING(priv->nmd->nifp, 0);
	priv->rx = NETMAP_RXRING(priv->nmd->nifp, 0);
	priv->cb = cb;
	priv->cb_param = param;
	be->fd = priv->nmd->fd;

	priv->mevp = mevent_add_disabled(be->fd, EVF_READ, cb, param);
	if (priv->mevp == NULL) {
		WPRINTF(("Could not register event\n"));
		return (-1);
	}

	return (0);
}