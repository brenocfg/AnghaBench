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
typedef  int /*<<< orphan*/  u8 ;
struct eap_sim_msg {scalar_t__ iv; int encr; int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_WARNING ; 
 int aes_128_cbc_encrypt (int /*<<< orphan*/ *,scalar_t__,size_t*,size_t) ; 
 int /*<<< orphan*/ * eap_sim_msg_add (struct eap_sim_msg*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  os_memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ wpabuf_head_u8 (int /*<<< orphan*/ ) ; 
 int wpabuf_len (int /*<<< orphan*/ ) ; 
 size_t* wpabuf_mhead_u8 (int /*<<< orphan*/ ) ; 

int eap_sim_msg_add_encr_end(struct eap_sim_msg *msg, u8 *k_encr, int attr_pad)
{
	size_t encr_len;

	if (msg == NULL || k_encr == NULL || msg->iv == 0 || msg->encr == 0)
		return -1;

	encr_len = wpabuf_len(msg->buf) - msg->encr - 4;
	if (encr_len % 16) {
		u8 *pos;
		int pad_len = 16 - (encr_len % 16);
		if (pad_len < 4) {
			wpa_printf(MSG_WARNING, "EAP-SIM: "
				   "eap_sim_msg_add_encr_end - invalid pad_len"
				   " %d", pad_len);
			return -1;
		}
		wpa_printf(MSG_DEBUG, "   *AT_PADDING");
		pos = eap_sim_msg_add(msg, attr_pad, 0, NULL, pad_len - 4);
		if (pos == NULL)
			return -1;
		os_memset(pos + 4, 0, pad_len - 4);
		encr_len += pad_len;
	}
	wpa_printf(MSG_DEBUG, "   (AT_ENCR_DATA data len %lu)",
		   (unsigned long) encr_len);
	wpabuf_mhead_u8(msg->buf)[msg->encr + 1] = encr_len / 4 + 1;
	return aes_128_cbc_encrypt(k_encr, wpabuf_head_u8(msg->buf) + msg->iv,
				   wpabuf_mhead_u8(msg->buf) + msg->encr + 4,
				   encr_len);
}