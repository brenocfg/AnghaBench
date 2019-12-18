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
typedef  int /*<<< orphan*/  const u8 ;
struct TYPE_2__ {int sec; } ;
struct wps_uuid_pin {int wildcard_uuid; size_t pin_len; int /*<<< orphan*/  list; TYPE_1__ expiration; int /*<<< orphan*/  flags; int /*<<< orphan*/ * pin; int /*<<< orphan*/  uuid; int /*<<< orphan*/  enrollee_addr; } ;
struct wps_registrar {int selected_registrar; scalar_t__ pbc; int /*<<< orphan*/  pins; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  PIN_EXPIRES ; 
 int /*<<< orphan*/  WPS_PBC_WALK_TIME ; 
 int /*<<< orphan*/  WPS_UUID_LEN ; 
 int /*<<< orphan*/  dl_list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eloop_cancel_timeout (int /*<<< orphan*/ ,struct wps_registrar*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eloop_register_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct wps_registrar*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_free (struct wps_uuid_pin*) ; 
 int /*<<< orphan*/  os_get_reltime (TYPE_1__*) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * os_memdup (int /*<<< orphan*/  const*,size_t) ; 
 struct wps_uuid_pin* os_zalloc (int) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_hexdump_ascii_key (int /*<<< orphan*/ ,char*,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  wps_registrar_add_authorized_mac (struct wps_registrar*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  wps_registrar_invalidate_unused (struct wps_registrar*) ; 
 int /*<<< orphan*/  wps_registrar_selected_registrar_changed (struct wps_registrar*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wps_registrar_set_selected_timeout ; 

int wps_registrar_add_pin(struct wps_registrar *reg, const u8 *addr,
			  const u8 *uuid, const u8 *pin, size_t pin_len,
			  int timeout)
{
	struct wps_uuid_pin *p;

	p = os_zalloc(sizeof(*p));
	if (p == NULL)
		return -1;
	if (addr)
		os_memcpy(p->enrollee_addr, addr, ETH_ALEN);
	if (uuid == NULL)
		p->wildcard_uuid = 1;
	else
		os_memcpy(p->uuid, uuid, WPS_UUID_LEN);
	p->pin = os_memdup(pin, pin_len);
	if (p->pin == NULL) {
		os_free(p);
		return -1;
	}
	p->pin_len = pin_len;

	if (timeout) {
		p->flags |= PIN_EXPIRES;
		os_get_reltime(&p->expiration);
		p->expiration.sec += timeout;
	}

	if (p->wildcard_uuid)
		wps_registrar_invalidate_unused(reg);

	dl_list_add(&reg->pins, &p->list);

	wpa_printf(MSG_DEBUG, "WPS: A new PIN configured (timeout=%d)",
		   timeout);
	wpa_hexdump(MSG_DEBUG, "WPS: UUID", uuid, WPS_UUID_LEN);
	wpa_hexdump_ascii_key(MSG_DEBUG, "WPS: PIN", pin, pin_len);
	reg->selected_registrar = 1;
	reg->pbc = 0;
	if (addr)
		wps_registrar_add_authorized_mac(reg, addr);
	else
		wps_registrar_add_authorized_mac(
			reg, (u8 *) "\xff\xff\xff\xff\xff\xff");
	wps_registrar_selected_registrar_changed(reg, 0);
	eloop_cancel_timeout(wps_registrar_set_selected_timeout, reg, NULL);
	eloop_register_timeout(WPS_PBC_WALK_TIME, 0,
			       wps_registrar_set_selected_timeout,
			       reg, NULL);

	return 0;
}