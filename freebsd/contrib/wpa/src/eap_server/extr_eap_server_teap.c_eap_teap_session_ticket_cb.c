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
typedef  int u8 ;
struct os_time {scalar_t__ sec; } ;
struct eap_teap_data {int* identity; size_t identity_len; int send_new_pac; scalar_t__ pac_key_refresh_time; int /*<<< orphan*/  pac_opaque_encr; } ;
typedef  scalar_t__ os_time_t ;

/* Variables and functions */
 int EAP_TEAP_PAC_KEY_LEN ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
#define  PAC_OPAQUE_TYPE_IDENTITY 131 
#define  PAC_OPAQUE_TYPE_KEY 130 
#define  PAC_OPAQUE_TYPE_LIFETIME 129 
#define  PAC_OPAQUE_TYPE_PAD 128 
 size_t PAC_TYPE_PAC_OPAQUE ; 
 size_t WPA_GET_BE16 (int const*) ; 
 scalar_t__ WPA_GET_BE32 (int*) ; 
 scalar_t__ aes_unwrap (int /*<<< orphan*/ ,int,size_t,int const*,int*) ; 
 int /*<<< orphan*/  os_free (int*) ; 
 scalar_t__ os_get_time (struct os_time*) ; 
 void* os_malloc (size_t) ; 
 int /*<<< orphan*/  os_memcpy (int*,int*,int) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,int const*,size_t) ; 
 int /*<<< orphan*/  wpa_hexdump_ascii (int /*<<< orphan*/ ,char*,int*,size_t) ; 
 int /*<<< orphan*/  wpa_hexdump_key (int /*<<< orphan*/ ,char*,int*,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int eap_teap_session_ticket_cb(void *ctx, const u8 *ticket, size_t len,
				      const u8 *client_random,
				      const u8 *server_random,
				      u8 *master_secret)
{
	struct eap_teap_data *data = ctx;
	const u8 *pac_opaque;
	size_t pac_opaque_len;
	u8 *buf, *pos, *end, *pac_key = NULL;
	os_time_t lifetime = 0;
	struct os_time now;
	u8 *identity = NULL;
	size_t identity_len = 0;

	wpa_printf(MSG_DEBUG, "EAP-TEAP: SessionTicket callback");
	wpa_hexdump(MSG_DEBUG, "EAP-TEAP: SessionTicket (PAC-Opaque)",
		    ticket, len);

	if (len < 4 || WPA_GET_BE16(ticket) != PAC_TYPE_PAC_OPAQUE) {
		wpa_printf(MSG_DEBUG, "EAP-TEAP: Ignore invalid SessionTicket");
		return 0;
	}

	pac_opaque_len = WPA_GET_BE16(ticket + 2);
	pac_opaque = ticket + 4;
	if (pac_opaque_len < 8 || pac_opaque_len % 8 ||
	    pac_opaque_len > len - 4) {
		wpa_printf(MSG_DEBUG,
			   "EAP-TEAP: Ignore invalid PAC-Opaque (len=%lu left=%lu)",
			   (unsigned long) pac_opaque_len,
			   (unsigned long) len);
		return 0;
	}
	wpa_hexdump(MSG_DEBUG, "EAP-TEAP: Received PAC-Opaque",
		    pac_opaque, pac_opaque_len);

	buf = os_malloc(pac_opaque_len - 8);
	if (!buf) {
		wpa_printf(MSG_DEBUG,
			   "EAP-TEAP: Failed to allocate memory for decrypting PAC-Opaque");
		return 0;
	}

	if (aes_unwrap(data->pac_opaque_encr, sizeof(data->pac_opaque_encr),
		       (pac_opaque_len - 8) / 8, pac_opaque, buf) < 0) {
		wpa_printf(MSG_DEBUG, "EAP-TEAP: Failed to decrypt PAC-Opaque");
		os_free(buf);
		/*
		 * This may have been caused by server changing the PAC-Opaque
		 * encryption key, so just ignore this PAC-Opaque instead of
		 * failing the authentication completely. Provisioning can now
		 * be used to provision a new PAC.
		 */
		return 0;
	}

	end = buf + pac_opaque_len - 8;
	wpa_hexdump_key(MSG_DEBUG, "EAP-TEAP: Decrypted PAC-Opaque",
			buf, end - buf);

	pos = buf;
	while (end - pos > 1) {
		u8 id, elen;

		id = *pos++;
		elen = *pos++;
		if (elen > end - pos)
			break;

		switch (id) {
		case PAC_OPAQUE_TYPE_PAD:
			goto done;
		case PAC_OPAQUE_TYPE_KEY:
			if (elen != EAP_TEAP_PAC_KEY_LEN) {
				wpa_printf(MSG_DEBUG,
					   "EAP-TEAP: Invalid PAC-Key length %d",
					   elen);
				os_free(buf);
				return -1;
			}
			pac_key = pos;
			wpa_hexdump_key(MSG_DEBUG,
					"EAP-TEAP: PAC-Key from decrypted PAC-Opaque",
					pac_key, EAP_TEAP_PAC_KEY_LEN);
			break;
		case PAC_OPAQUE_TYPE_LIFETIME:
			if (elen != 4) {
				wpa_printf(MSG_DEBUG,
					   "EAP-TEAP: Invalid PAC-Key lifetime length %d",
					   elen);
				os_free(buf);
				return -1;
			}
			lifetime = WPA_GET_BE32(pos);
			break;
		case PAC_OPAQUE_TYPE_IDENTITY:
			identity = pos;
			identity_len = elen;
			break;
		}

		pos += elen;
	}
done:

	if (!pac_key) {
		wpa_printf(MSG_DEBUG,
			   "EAP-TEAP: No PAC-Key included in PAC-Opaque");
		os_free(buf);
		return -1;
	}

	if (identity) {
		wpa_hexdump_ascii(MSG_DEBUG,
				  "EAP-TEAP: Identity from PAC-Opaque",
				  identity, identity_len);
		os_free(data->identity);
		data->identity = os_malloc(identity_len);
		if (data->identity) {
			os_memcpy(data->identity, identity, identity_len);
			data->identity_len = identity_len;
		}
	}

	if (os_get_time(&now) < 0 || lifetime <= 0 || now.sec > lifetime) {
		wpa_printf(MSG_DEBUG,
			   "EAP-TEAP: PAC-Key not valid anymore (lifetime=%ld now=%ld)",
			   lifetime, now.sec);
		data->send_new_pac = 2;
		/*
		 * Allow PAC to be used to allow a PAC update with some level
		 * of server authentication (i.e., do not fall back to full TLS
		 * handshake since we cannot be sure that the peer would be
		 * able to validate server certificate now). However, reject
		 * the authentication since the PAC was not valid anymore. Peer
		 * can connect again with the newly provisioned PAC after this.
		 */
	} else if (lifetime - now.sec < data->pac_key_refresh_time) {
		wpa_printf(MSG_DEBUG,
			   "EAP-TEAP: PAC-Key soft timeout; send an update if authentication succeeds");
		data->send_new_pac = 1;
	}

	/* EAP-TEAP uses PAC-Key as the TLS master_secret */
	os_memcpy(master_secret, pac_key, EAP_TEAP_PAC_KEY_LEN);

	os_free(buf);

	return 1;
}