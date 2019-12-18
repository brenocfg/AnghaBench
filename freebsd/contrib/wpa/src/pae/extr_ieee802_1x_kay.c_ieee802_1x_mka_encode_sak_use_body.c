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
typedef  scalar_t__ u32 ;
struct wpabuf {int dummy; } ;
struct ieee802_1x_mka_sak_use_body {int ptx; int prx; int delay_protect; void* lrx; void* ltx; void* orx; void* otx; void* okn; int /*<<< orphan*/  osrv_mi; int /*<<< orphan*/  oan; void* lkn; int /*<<< orphan*/  lsrv_mi; scalar_t__ lan; void* olpn; void* llpn; int /*<<< orphan*/  type; } ;
struct TYPE_2__ {scalar_t__ kn; int /*<<< orphan*/  mi; } ;
struct ieee802_1x_mka_participant {TYPE_1__ oki; TYPE_1__ lki; int /*<<< orphan*/  oan; void* ltx; void* lrx; scalar_t__ lan; void* new_sak; scalar_t__ is_key_server; struct ieee802_1x_kay* kay; } ;
struct ieee802_1x_kay {scalar_t__ mka_hello_time; scalar_t__ pn_exhaustion; scalar_t__ macsec_validate; void* rx_enable; void* port_enable; void* tx_enable; int /*<<< orphan*/  macsec_protect; } ;

/* Variables and functions */
 void* FALSE ; 
 scalar_t__ MKA_BOUNDED_HELLO_TIME ; 
 unsigned int MKA_HDR_LEN ; 
 int /*<<< orphan*/  MKA_SAK_USE ; 
 int /*<<< orphan*/  MSG_WARNING ; 
 scalar_t__ Strict ; 
 void* TRUE ; 
 void* host_to_be32 (scalar_t__) ; 
 int /*<<< orphan*/  ieee802_1x_mka_dump_sak_use_body (struct ieee802_1x_mka_sak_use_body*) ; 
 scalar_t__ ieee802_1x_mka_get_lpn (struct ieee802_1x_mka_participant*,TYPE_1__*) ; 
 unsigned int ieee802_1x_mka_get_sak_use_length (struct ieee802_1x_mka_participant*) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_mka_param_body_len (struct ieee802_1x_mka_sak_use_body*,unsigned int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 struct ieee802_1x_mka_sak_use_body* wpabuf_put (struct wpabuf*,unsigned int) ; 

__attribute__((used)) static int
ieee802_1x_mka_encode_sak_use_body(
	struct ieee802_1x_mka_participant *participant,
	struct wpabuf *buf)
{
	struct ieee802_1x_mka_sak_use_body *body;
	struct ieee802_1x_kay *kay = participant->kay;
	unsigned int length;
	u32 pn = 1;

	length = ieee802_1x_mka_get_sak_use_length(participant);
	body = wpabuf_put(buf, length);

	body->type = MKA_SAK_USE;
	set_mka_param_body_len(body, length - MKA_HDR_LEN);

	if (length == MKA_HDR_LEN) {
		body->ptx = TRUE;
		body->prx = TRUE;
		body->lan = 0;
		body->lrx = FALSE;
		body->ltx = FALSE;
		body->delay_protect = FALSE;
		return 0;
	}

	/* data delay protect */
	body->delay_protect = kay->mka_hello_time <= MKA_BOUNDED_HELLO_TIME;
	/* lowest accept packet number */
	pn = ieee802_1x_mka_get_lpn(participant, &participant->lki);
	if (pn > kay->pn_exhaustion) {
		wpa_printf(MSG_WARNING, "KaY: My LPN exhaustion");
		if (participant->is_key_server)
			participant->new_sak = TRUE;
	}

	body->llpn = host_to_be32(pn);
	pn = ieee802_1x_mka_get_lpn(participant, &participant->oki);
	body->olpn = host_to_be32(pn);

	/* plain tx, plain rx */
	body->ptx = !kay->macsec_protect;
	body->prx = kay->macsec_validate != Strict;

	/* latest key: rx, tx, key server member identifier key number */
	body->lan = participant->lan;
	os_memcpy(body->lsrv_mi, participant->lki.mi, sizeof(body->lsrv_mi));
	body->lkn = host_to_be32(participant->lki.kn);
	body->lrx = participant->lrx;
	body->ltx = participant->ltx;

	/* old key: rx, tx, key server member identifier key number */
	body->oan = participant->oan;
	if (participant->oki.kn != participant->lki.kn &&
	    participant->oki.kn != 0) {
		body->otx = TRUE;
		body->orx = TRUE;
		os_memcpy(body->osrv_mi, participant->oki.mi,
			  sizeof(body->osrv_mi));
		body->okn = host_to_be32(participant->oki.kn);
	} else {
		body->otx = FALSE;
		body->orx = FALSE;
	}

	/* set CP's variable */
	if (body->ltx) {
		kay->tx_enable = TRUE;
		kay->port_enable = TRUE;
	}
	if (body->lrx)
		kay->rx_enable = TRUE;

	ieee802_1x_mka_dump_sak_use_body(body);
	return 0;
}