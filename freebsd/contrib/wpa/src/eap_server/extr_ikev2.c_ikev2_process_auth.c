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
struct ikev2_initiator_data {int peer_auth; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  MSG_MSGDUMP ; 
#define  PEER_AUTH_CERT 129 
#define  PEER_AUTH_SECRET 128 
 int ikev2_process_auth_cert (struct ikev2_initiator_data*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,size_t) ; 
 int ikev2_process_auth_secret (struct ikev2_initiator_data*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int ikev2_process_auth(struct ikev2_initiator_data *data,
			      const u8 *auth, size_t auth_len)
{
	u8 auth_method;

	if (auth == NULL) {
		wpa_printf(MSG_INFO, "IKEV2: No Authentication Payload");
		return -1;
	}

	if (auth_len < 4) {
		wpa_printf(MSG_INFO, "IKEV2: Too short Authentication "
			   "Payload");
		return -1;
	}

	auth_method = auth[0];
	auth += 4;
	auth_len -= 4;

	wpa_printf(MSG_DEBUG, "IKEV2: Auth Method %d", auth_method);
	wpa_hexdump(MSG_MSGDUMP, "IKEV2: Authentication Data", auth, auth_len);

	switch (data->peer_auth) {
	case PEER_AUTH_CERT:
		return ikev2_process_auth_cert(data, auth_method, auth,
					       auth_len);
	case PEER_AUTH_SECRET:
		return ikev2_process_auth_secret(data, auth_method, auth,
						 auth_len);
	}

	return -1;
}