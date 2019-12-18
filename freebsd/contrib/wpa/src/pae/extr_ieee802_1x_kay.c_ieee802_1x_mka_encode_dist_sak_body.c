#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct wpabuf {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  len; int /*<<< orphan*/  key; } ;
struct ieee802_1x_mka_participant {TYPE_3__ kek; TYPE_2__* kay; struct data_key* new_key; } ;
struct ieee802_1x_mka_dist_sak_body {scalar_t__ sak; int /*<<< orphan*/  kn; scalar_t__ dan; scalar_t__ confid_offset; int /*<<< orphan*/  type; } ;
struct TYPE_5__ {int /*<<< orphan*/  kn; } ;
struct data_key {int /*<<< orphan*/  key; TYPE_1__ key_identifier; scalar_t__ an; scalar_t__ confidentiality_offset; } ;
typedef  int /*<<< orphan*/  be64 ;
struct TYPE_8__ {int sak_len; int /*<<< orphan*/  id; } ;
struct TYPE_6__ {unsigned int macsec_csindex; } ;

/* Variables and functions */
 int CS_ID_LEN ; 
 unsigned int CS_TABLE_SIZE ; 
 unsigned int DEFAULT_CS_INDEX ; 
 int /*<<< orphan*/  MKA_DISTRIBUTED_SAK ; 
 unsigned int MKA_HDR_LEN ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 scalar_t__ aes_wrap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_4__* cipher_suite_tbl ; 
 int /*<<< orphan*/  host_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  host_to_be64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee802_1x_mka_dump_dist_sak_body (struct ieee802_1x_mka_dist_sak_body*) ; 
 unsigned int ieee802_1x_mka_get_dist_sak_length (struct ieee802_1x_mka_participant*) ; 
 int /*<<< orphan*/  os_memcpy (scalar_t__,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  set_mka_param_body_len (struct ieee802_1x_mka_dist_sak_body*,unsigned int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 struct ieee802_1x_mka_dist_sak_body* wpabuf_put (struct wpabuf*,unsigned int) ; 

__attribute__((used)) static int
ieee802_1x_mka_encode_dist_sak_body(
	struct ieee802_1x_mka_participant *participant,
	struct wpabuf *buf)
{
	struct ieee802_1x_mka_dist_sak_body *body;
	struct data_key *sak;
	unsigned int length;
	unsigned int cs_index;
	int sak_pos;

	length = ieee802_1x_mka_get_dist_sak_length(participant);
	body = wpabuf_put(buf, length);
	body->type = MKA_DISTRIBUTED_SAK;
	set_mka_param_body_len(body, length - MKA_HDR_LEN);
	if (length == MKA_HDR_LEN) {
		body->confid_offset = 0;
		body->dan = 0;
		return 0;
	}

	sak = participant->new_key;
	if (!sak) {
		wpa_printf(MSG_DEBUG,
			   "KaY: No SAK available to build Distributed SAK parameter set");
		return -1;
	}
	body->confid_offset = sak->confidentiality_offset;
	body->dan = sak->an;
	body->kn = host_to_be32(sak->key_identifier.kn);
	cs_index = participant->kay->macsec_csindex;
	sak_pos = 0;
	if (cs_index >= CS_TABLE_SIZE)
		return -1;
	if (cs_index != DEFAULT_CS_INDEX) {
		be64 cs;

		cs = host_to_be64(cipher_suite_tbl[cs_index].id);
		os_memcpy(body->sak, &cs, CS_ID_LEN);
		sak_pos = CS_ID_LEN;
	}
	if (aes_wrap(participant->kek.key, participant->kek.len,
		     cipher_suite_tbl[cs_index].sak_len / 8,
		     sak->key, body->sak + sak_pos)) {
		wpa_printf(MSG_ERROR, "KaY: AES wrap failed");
		return -1;
	}

	ieee802_1x_mka_dump_dist_sak_body(body);

	return 0;
}