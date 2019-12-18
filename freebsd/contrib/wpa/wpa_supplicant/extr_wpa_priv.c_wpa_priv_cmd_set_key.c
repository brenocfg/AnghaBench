#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct wpa_priv_interface {int /*<<< orphan*/ * drv_priv; int /*<<< orphan*/  ifname; TYPE_1__* driver; } ;
struct privsep_cmd_set_key {scalar_t__ key_len; int /*<<< orphan*/ * key; scalar_t__ seq_len; int /*<<< orphan*/ * seq; int /*<<< orphan*/  set_tx; int /*<<< orphan*/  key_idx; int /*<<< orphan*/  addr; int /*<<< orphan*/  alg; } ;
struct TYPE_2__ {int (* set_key ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,scalar_t__) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static void wpa_priv_cmd_set_key(struct wpa_priv_interface *iface,
				 void *buf, size_t len)
{
	struct privsep_cmd_set_key *params;
	int res;

	if (iface->drv_priv == NULL || iface->driver->set_key == NULL)
		return;

	if (len != sizeof(*params)) {
		wpa_printf(MSG_DEBUG, "Invalid set_key request");
		return;
	}

	params = buf;

	res = iface->driver->set_key(iface->ifname, iface->drv_priv,
				     params->alg,
				     params->addr, params->key_idx,
				     params->set_tx,
				     params->seq_len ? params->seq : NULL,
				     params->seq_len,
				     params->key_len ? params->key : NULL,
				     params->key_len);
	wpa_printf(MSG_DEBUG, "drv->set_key: res=%d", res);
}