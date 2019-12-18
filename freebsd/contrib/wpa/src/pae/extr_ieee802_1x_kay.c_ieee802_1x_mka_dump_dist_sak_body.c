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
struct ieee802_1x_mka_dist_sak_body {size_t dan; size_t confid_offset; int /*<<< orphan*/  sak; int /*<<< orphan*/  kn; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 size_t be_to_host32 (int /*<<< orphan*/ ) ; 
 size_t get_mka_param_body_len (struct ieee802_1x_mka_dist_sak_body*) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static void
ieee802_1x_mka_dump_dist_sak_body(struct ieee802_1x_mka_dist_sak_body *body)
{
	size_t body_len;

	if (body == NULL)
		return;

	/* IEEE Std 802.1X-2010, Figure 11-11 and 11-12 */
	body_len = get_mka_param_body_len(body);
	wpa_printf(MSG_DEBUG, "Distributed SAK parameter set");
	wpa_printf(MSG_DEBUG, "\tDistributed AN........: %d", body->dan);
	wpa_printf(MSG_DEBUG, "\tConfidentiality Offset: %d",
		   body->confid_offset);
	wpa_printf(MSG_DEBUG, "\tBody Length...........: %zu", body_len);
	if (!body_len)
		return;

	wpa_printf(MSG_DEBUG, "\tKey Number............: %d",
		   be_to_host32(body->kn));
	/* TODO: Other than GCM-AES-128 case: MACsec Cipher Suite */
	wpa_hexdump(MSG_DEBUG, "\tAES Key Wrap of SAK...:", body->sak, 24);
}