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
struct ikev2_responder_data {size_t i_nonce_len; int /*<<< orphan*/  i_nonce; } ;

/* Variables and functions */
 size_t IKEV2_NONCE_MAX_LEN ; 
 size_t IKEV2_NONCE_MIN_LEN ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  MSG_MSGDUMP ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int ikev2_process_ni(struct ikev2_responder_data *data,
			    const u8 *ni, size_t ni_len)
{
	if (ni == NULL) {
		wpa_printf(MSG_INFO, "IKEV2: Ni not received");
		return -1;
	}

	if (ni_len < IKEV2_NONCE_MIN_LEN || ni_len > IKEV2_NONCE_MAX_LEN) {
		wpa_printf(MSG_INFO, "IKEV2: Invalid Ni length %ld",
		           (long) ni_len);
		return -1;
	}

	data->i_nonce_len = ni_len;
	os_memcpy(data->i_nonce, ni, ni_len);
	wpa_hexdump(MSG_MSGDUMP, "IKEV2: Ni",
		    data->i_nonce, data->i_nonce_len);

	return 0;
}