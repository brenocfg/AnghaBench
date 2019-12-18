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
struct nm_config_info {scalar_t__ num_tx_rings; scalar_t__ num_tx_descs; scalar_t__ num_rx_rings; scalar_t__ num_rx_descs; scalar_t__ rx_buf_maxsize; } ;
struct netmap_adapter {scalar_t__ num_tx_rings; scalar_t__ num_tx_desc; scalar_t__ num_rx_rings; scalar_t__ num_rx_desc; scalar_t__ rx_buf_maxsize; scalar_t__ active_fds; int /*<<< orphan*/  name; scalar_t__ (* nm_config ) (struct netmap_adapter*,struct nm_config_info*) ;} ;
typedef  int /*<<< orphan*/  info ;

/* Variables and functions */
 int /*<<< orphan*/  bzero (struct nm_config_info*,int) ; 
 scalar_t__ netmap_verbose ; 
 int /*<<< orphan*/  nm_prerr (char*,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  nm_prinf (char*,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ stub1 (struct netmap_adapter*,struct nm_config_info*) ; 

int
netmap_update_config(struct netmap_adapter *na)
{
	struct nm_config_info info;

	bzero(&info, sizeof(info));
	if (na->nm_config == NULL ||
	    na->nm_config(na, &info)) {
		/* take whatever we had at init time */
		info.num_tx_rings = na->num_tx_rings;
		info.num_tx_descs = na->num_tx_desc;
		info.num_rx_rings = na->num_rx_rings;
		info.num_rx_descs = na->num_rx_desc;
		info.rx_buf_maxsize = na->rx_buf_maxsize;
	}

	if (na->num_tx_rings == info.num_tx_rings &&
	    na->num_tx_desc == info.num_tx_descs &&
	    na->num_rx_rings == info.num_rx_rings &&
	    na->num_rx_desc == info.num_rx_descs &&
	    na->rx_buf_maxsize == info.rx_buf_maxsize)
		return 0; /* nothing changed */
	if (na->active_fds == 0) {
		na->num_tx_rings = info.num_tx_rings;
		na->num_tx_desc = info.num_tx_descs;
		na->num_rx_rings = info.num_rx_rings;
		na->num_rx_desc = info.num_rx_descs;
		na->rx_buf_maxsize = info.rx_buf_maxsize;
		if (netmap_verbose)
			nm_prinf("configuration changed for %s: txring %d x %d, "
				"rxring %d x %d, rxbufsz %d",
				na->name, na->num_tx_rings, na->num_tx_desc,
				na->num_rx_rings, na->num_rx_desc, na->rx_buf_maxsize);
		return 0;
	}
	nm_prerr("WARNING: configuration changed for %s while active: "
		"txring %d x %d, rxring %d x %d, rxbufsz %d",
		na->name, info.num_tx_rings, info.num_tx_descs,
		info.num_rx_rings, info.num_rx_descs,
		info.rx_buf_maxsize);
	return 1;
}