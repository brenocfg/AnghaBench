#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct nmreq {int nr_arg1; int /*<<< orphan*/  nr_cmd; } ;
struct netmap_priv {int /*<<< orphan*/  ifname; } ;
struct net_backend {int be_vnet_hdr_len; int /*<<< orphan*/  fd; scalar_t__ opaque; } ;

/* Variables and functions */
 int /*<<< orphan*/  NETMAP_BDG_VNET_HDR ; 
 int /*<<< orphan*/  NIOCREGIF ; 
 int /*<<< orphan*/  WPRINTF (char*) ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nmreq*) ; 
 int /*<<< orphan*/  nmreq_init (struct nmreq*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
netmap_set_vnet_hdr_len(struct net_backend *be, int vnet_hdr_len)
{
	int err;
	struct nmreq req;
	struct netmap_priv *priv = (struct netmap_priv *)be->opaque;

	nmreq_init(&req, priv->ifname);
	req.nr_cmd = NETMAP_BDG_VNET_HDR;
	req.nr_arg1 = vnet_hdr_len;
	err = ioctl(be->fd, NIOCREGIF, &req);
	if (err) {
		WPRINTF(("Unable to set vnet header length %d\n",
				vnet_hdr_len));
		return (err);
	}

	be->be_vnet_hdr_len = vnet_hdr_len;

	return (0);
}