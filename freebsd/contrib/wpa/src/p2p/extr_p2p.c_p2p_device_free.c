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
struct TYPE_4__ {int /*<<< orphan*/ * p2ps_instance; int /*<<< orphan*/ * vendor_elems; int /*<<< orphan*/ * wfd_subelems; int /*<<< orphan*/ ** wps_vendor_ext; int /*<<< orphan*/  p2p_device_addr; } ;
struct p2p_device {int flags; TYPE_2__ info; int /*<<< orphan*/ * go_neg_conf; } ;
struct p2p_data {TYPE_1__* cfg; struct p2p_device* pending_client_disc_go; struct p2p_device* sd_peer; struct p2p_device* invite_peer; struct p2p_device* go_neg_peer; } ;
struct TYPE_3__ {int /*<<< orphan*/  cb_ctx; int /*<<< orphan*/  (* dev_lost ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int P2P_DEV_REPORTED_ONCE ; 
 int P2P_MAX_WPS_VENDOR_EXT ; 
 int /*<<< orphan*/  os_free (struct p2p_device*) ; 
 int /*<<< orphan*/  p2p_go_neg_failed (struct p2p_data*,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpabuf_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void p2p_device_free(struct p2p_data *p2p, struct p2p_device *dev)
{
	int i;

	if (p2p->go_neg_peer == dev) {
		/*
		 * If GO Negotiation is in progress, report that it has failed.
		 */
		p2p_go_neg_failed(p2p, -1);
	}
	if (p2p->invite_peer == dev)
		p2p->invite_peer = NULL;
	if (p2p->sd_peer == dev)
		p2p->sd_peer = NULL;
	if (p2p->pending_client_disc_go == dev)
		p2p->pending_client_disc_go = NULL;

	/* dev_lost() device, but only if it was previously dev_found() */
	if (dev->flags & P2P_DEV_REPORTED_ONCE)
		p2p->cfg->dev_lost(p2p->cfg->cb_ctx,
				   dev->info.p2p_device_addr);

	for (i = 0; i < P2P_MAX_WPS_VENDOR_EXT; i++) {
		wpabuf_free(dev->info.wps_vendor_ext[i]);
		dev->info.wps_vendor_ext[i] = NULL;
	}

	wpabuf_free(dev->info.wfd_subelems);
	wpabuf_free(dev->info.vendor_elems);
	wpabuf_free(dev->go_neg_conf);
	wpabuf_free(dev->info.p2ps_instance);

	os_free(dev);
}