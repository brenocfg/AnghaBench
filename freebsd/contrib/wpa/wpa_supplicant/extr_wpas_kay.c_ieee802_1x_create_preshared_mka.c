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
struct wpa_supplicant {TYPE_1__* kay; } ;
struct wpa_ssid {int mka_psk_set; int /*<<< orphan*/  mka_ckn; int /*<<< orphan*/  mka_ckn_len; int /*<<< orphan*/  mka_cak; int /*<<< orphan*/  mka_cak_len; } ;
struct mka_key_name {int /*<<< orphan*/  len; int /*<<< orphan*/  name; int /*<<< orphan*/  key; } ;
struct mka_key {int /*<<< orphan*/  len; int /*<<< orphan*/  name; int /*<<< orphan*/  key; } ;
struct TYPE_2__ {scalar_t__ policy; } ;

/* Variables and functions */
 scalar_t__ DO_NOT_SECURE ; 
 int /*<<< orphan*/  FALSE ; 
 int MKA_PSK_SET ; 
 int /*<<< orphan*/  PSK ; 
 scalar_t__ ieee802_1x_alloc_kay_sm (struct wpa_supplicant*,struct wpa_ssid*) ; 
 int /*<<< orphan*/  ieee802_1x_dealloc_kay_sm (struct wpa_supplicant*) ; 
 void* ieee802_1x_kay_create_mka (TYPE_1__*,struct mka_key_name*,struct mka_key_name*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_free (struct mka_key_name*) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mka_key_name* os_zalloc (int) ; 

void * ieee802_1x_create_preshared_mka(struct wpa_supplicant *wpa_s,
				       struct wpa_ssid *ssid)
{
	struct mka_key *cak;
	struct mka_key_name *ckn;
	void *res = NULL;

	if ((ssid->mka_psk_set & MKA_PSK_SET) != MKA_PSK_SET)
		goto end;

	ckn = os_zalloc(sizeof(*ckn));
	if (!ckn)
		goto end;

	cak = os_zalloc(sizeof(*cak));
	if (!cak)
		goto free_ckn;

	if (ieee802_1x_alloc_kay_sm(wpa_s, ssid) < 0 || !wpa_s->kay)
		goto free_cak;

	if (wpa_s->kay->policy == DO_NOT_SECURE)
		goto dealloc;

	cak->len = ssid->mka_cak_len;
	os_memcpy(cak->key, ssid->mka_cak, cak->len);

	ckn->len = ssid->mka_ckn_len;
	os_memcpy(ckn->name, ssid->mka_ckn, ckn->len);

	res = ieee802_1x_kay_create_mka(wpa_s->kay, ckn, cak, 0, PSK, FALSE);
	if (res)
		goto free_cak;

dealloc:
	/* Failed to create MKA */
	ieee802_1x_dealloc_kay_sm(wpa_s);
free_cak:
	os_free(cak);
free_ckn:
	os_free(ckn);
end:
	return res;
}