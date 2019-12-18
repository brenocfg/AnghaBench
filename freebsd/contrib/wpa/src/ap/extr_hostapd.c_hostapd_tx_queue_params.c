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
struct hostapd_tx_queue_params {int /*<<< orphan*/  burst; int /*<<< orphan*/  cwmax; int /*<<< orphan*/  cwmin; int /*<<< orphan*/  aifs; } ;
struct hostapd_iface {TYPE_1__* conf; int /*<<< orphan*/ * mconf; struct hostapd_data** bss; } ;
struct hostapd_data {TYPE_2__* conf; } ;
struct TYPE_4__ {int mesh; } ;
struct TYPE_3__ {struct hostapd_tx_queue_params* tx_queue; } ;

/* Variables and functions */
 int MESH_ENABLED ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int NUM_TX_QUEUES ; 
 scalar_t__ hostapd_set_tx_queue_params (struct hostapd_data*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void hostapd_tx_queue_params(struct hostapd_iface *iface)
{
	struct hostapd_data *hapd = iface->bss[0];
	int i;
	struct hostapd_tx_queue_params *p;

#ifdef CONFIG_MESH
	if ((hapd->conf->mesh & MESH_ENABLED) && iface->mconf == NULL)
		return;
#endif /* CONFIG_MESH */

	for (i = 0; i < NUM_TX_QUEUES; i++) {
		p = &iface->conf->tx_queue[i];

		if (hostapd_set_tx_queue_params(hapd, i, p->aifs, p->cwmin,
						p->cwmax, p->burst)) {
			wpa_printf(MSG_DEBUG, "Failed to set TX queue "
				   "parameters for queue %d.", i);
			/* Continue anyway */
		}
	}
}