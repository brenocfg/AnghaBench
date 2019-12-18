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
struct wpa_supplicant {char* imsi; int /*<<< orphan*/ * scard; int /*<<< orphan*/  eapol; int /*<<< orphan*/  wpa; int /*<<< orphan*/  mnc_len; TYPE_1__* conf; } ;
struct TYPE_2__ {scalar_t__ pcsc_pin; int /*<<< orphan*/  pcsc_reader; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  eapol_sm_register_scard_ctx (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scard_deinit (int /*<<< orphan*/ *) ; 
 scalar_t__ scard_get_imsi (int /*<<< orphan*/ *,char*,size_t*) ; 
 int /*<<< orphan*/  scard_get_mnc_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * scard_init (int /*<<< orphan*/ ) ; 
 scalar_t__ scard_set_pin (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  wpa_msg (struct wpa_supplicant*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_sm_set_scard_ctx (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pcsc_reader_init(struct wpa_supplicant *wpa_s)
{
#ifdef PCSC_FUNCS
	size_t len;

	if (!wpa_s->conf->pcsc_reader)
		return 0;

	wpa_s->scard = scard_init(wpa_s->conf->pcsc_reader);
	if (!wpa_s->scard)
		return 1;

	if (wpa_s->conf->pcsc_pin &&
	    scard_set_pin(wpa_s->scard, wpa_s->conf->pcsc_pin) < 0) {
		scard_deinit(wpa_s->scard);
		wpa_s->scard = NULL;
		wpa_msg(wpa_s, MSG_ERROR, "PC/SC PIN validation failed");
		return -1;
	}

	len = sizeof(wpa_s->imsi) - 1;
	if (scard_get_imsi(wpa_s->scard, wpa_s->imsi, &len)) {
		scard_deinit(wpa_s->scard);
		wpa_s->scard = NULL;
		wpa_msg(wpa_s, MSG_ERROR, "Could not read IMSI");
		return -1;
	}
	wpa_s->imsi[len] = '\0';

	wpa_s->mnc_len = scard_get_mnc_len(wpa_s->scard);

	wpa_printf(MSG_DEBUG, "SCARD: IMSI %s (MNC length %d)",
		   wpa_s->imsi, wpa_s->mnc_len);

	wpa_sm_set_scard_ctx(wpa_s->wpa, wpa_s->scard);
	eapol_sm_register_scard_ctx(wpa_s->eapol, wpa_s->scard);
#endif /* PCSC_FUNCS */

	return 0;
}