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
struct netlink_config {int /*<<< orphan*/  newlink_cb; struct atheros_driver_data* ctx; } ;
struct atheros_driver_data {int /*<<< orphan*/ * netlink; } ;

/* Variables and functions */
 int /*<<< orphan*/  atheros_get_we_version (struct atheros_driver_data*) ; 
 int /*<<< orphan*/  atheros_wireless_event_rtm_newlink ; 
 int /*<<< orphan*/ * netlink_init (struct netlink_config*) ; 
 int /*<<< orphan*/  os_free (struct netlink_config*) ; 
 struct netlink_config* os_zalloc (int) ; 

__attribute__((used)) static int
atheros_wireless_event_init(struct atheros_driver_data *drv)
{
	struct netlink_config *cfg;

	atheros_get_we_version(drv);

	cfg = os_zalloc(sizeof(*cfg));
	if (cfg == NULL)
		return -1;
	cfg->ctx = drv;
	cfg->newlink_cb = atheros_wireless_event_rtm_newlink;
	drv->netlink = netlink_init(cfg);
	if (drv->netlink == NULL) {
		os_free(cfg);
		return -1;
	}

	return 0;
}