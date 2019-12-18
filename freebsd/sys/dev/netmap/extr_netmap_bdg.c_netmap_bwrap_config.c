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
struct nm_config_info {int /*<<< orphan*/  rx_buf_maxsize; int /*<<< orphan*/  num_rx_descs; int /*<<< orphan*/  num_rx_rings; int /*<<< orphan*/  num_tx_descs; int /*<<< orphan*/  num_tx_rings; } ;
struct netmap_bwrap_adapter {struct netmap_adapter* hwna; } ;
struct netmap_adapter {int /*<<< orphan*/  rx_buf_maxsize; int /*<<< orphan*/  num_tx_desc; int /*<<< orphan*/  num_tx_rings; int /*<<< orphan*/  num_rx_desc; int /*<<< orphan*/  num_rx_rings; int /*<<< orphan*/  na_lut; int /*<<< orphan*/  nm_mem; } ;

/* Variables and functions */
 int netmap_mem_get_lut (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netmap_update_config (struct netmap_adapter*) ; 

__attribute__((used)) static int
netmap_bwrap_config(struct netmap_adapter *na, struct nm_config_info *info)
{
	struct netmap_bwrap_adapter *bna =
		(struct netmap_bwrap_adapter *)na;
	struct netmap_adapter *hwna = bna->hwna;
	int error;

	/* Forward the request to the hwna. It may happen that nobody
	 * registered hwna yet, so netmap_mem_get_lut() may have not
	 * been called yet. */
	error = netmap_mem_get_lut(hwna->nm_mem, &hwna->na_lut);
	if (error)
		return error;
	netmap_update_config(hwna);
	/* swap the results and propagate */
	info->num_tx_rings = hwna->num_rx_rings;
	info->num_tx_descs = hwna->num_rx_desc;
	info->num_rx_rings = hwna->num_tx_rings;
	info->num_rx_descs = hwna->num_tx_desc;
	info->rx_buf_maxsize = hwna->rx_buf_maxsize;

	return 0;
}