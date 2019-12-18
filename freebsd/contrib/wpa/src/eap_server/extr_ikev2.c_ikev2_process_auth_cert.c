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
typedef  scalar_t__ u8 ;
struct ikev2_initiator_data {int dummy; } ;

/* Variables and functions */
 scalar_t__ AUTH_RSA_SIGN ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,scalar_t__) ; 

__attribute__((used)) static int ikev2_process_auth_cert(struct ikev2_initiator_data *data,
				   u8 method, const u8 *auth, size_t auth_len)
{
	if (method != AUTH_RSA_SIGN) {
		wpa_printf(MSG_INFO, "IKEV2: Unsupported authentication "
			   "method %d", method);
		return -1;
	}

	/* TODO: validate AUTH */
	return 0;
}