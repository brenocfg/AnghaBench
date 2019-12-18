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
struct macsec_qca_data {int /*<<< orphan*/  secy_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  nss_macsec_secy_en_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nss_macsec_secy_rx_sc_del_all (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nss_macsec_secy_tx_sc_del_all (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __macsec_drv_deinit(struct macsec_qca_data *drv)
{
	nss_macsec_secy_en_set(drv->secy_id, FALSE);
	nss_macsec_secy_rx_sc_del_all(drv->secy_id);
	nss_macsec_secy_tx_sc_del_all(drv->secy_id);
}