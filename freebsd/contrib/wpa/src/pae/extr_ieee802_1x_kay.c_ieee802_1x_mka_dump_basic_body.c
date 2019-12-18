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
struct ieee802_1x_mka_basic_body {size_t version; size_t priority; size_t key_server; size_t macsec_desired; size_t macsec_capability; int /*<<< orphan*/  ckn; int /*<<< orphan*/  algo_agility; int /*<<< orphan*/  actor_mn; int /*<<< orphan*/  actor_mi; int /*<<< orphan*/  actor_sci; } ;

/* Variables and functions */
 scalar_t__ MKA_HDR_LEN ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 size_t algo_agility_txt (int /*<<< orphan*/ ) ; 
 size_t be_to_host32 (int /*<<< orphan*/ ) ; 
 size_t get_mka_param_body_len (struct ieee802_1x_mka_basic_body*) ; 
 size_t mi_txt (int /*<<< orphan*/ ) ; 
 size_t sci_txt (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static void
ieee802_1x_mka_dump_basic_body(struct ieee802_1x_mka_basic_body *body)
{
	size_t body_len;

	if (!body)
		return;

	/* IEEE Std 802.1X-2010, Figure 11-8 */
	body_len = get_mka_param_body_len(body);
	wpa_printf(MSG_DEBUG, "MKA Basic Parameter Set");
	wpa_printf(MSG_DEBUG, "\tMKA Version Identifier: %d", body->version);
	wpa_printf(MSG_DEBUG, "\tKey Server Priority: %d", body->priority);
	wpa_printf(MSG_DEBUG, "\tKey Server: %d", body->key_server);
	wpa_printf(MSG_DEBUG, "\tMACsec Desired: %d", body->macsec_desired);
	wpa_printf(MSG_DEBUG, "\tMACsec Capability: %d",
		   body->macsec_capability);
	wpa_printf(MSG_DEBUG, "\tParameter set body length: %zu", body_len);
	wpa_printf(MSG_DEBUG, "\tSCI: %s", sci_txt(&body->actor_sci));
	wpa_printf(MSG_DEBUG, "\tActor's Member Identifier: %s",
		   mi_txt(body->actor_mi));
	wpa_printf(MSG_DEBUG, "\tActor's Message Number: %d",
		   be_to_host32(body->actor_mn));
	wpa_printf(MSG_DEBUG, "\tAlgorithm Agility: %s",
		   algo_agility_txt(body->algo_agility));
	wpa_hexdump(MSG_DEBUG, "\tCAK Name", body->ckn,
		    body_len + MKA_HDR_LEN - sizeof(*body));
}