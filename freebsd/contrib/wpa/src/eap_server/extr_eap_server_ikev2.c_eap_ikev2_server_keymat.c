#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  prf; } ;
struct TYPE_4__ {int /*<<< orphan*/  r_nonce_len; int /*<<< orphan*/  r_nonce; int /*<<< orphan*/  i_nonce_len; int /*<<< orphan*/  i_nonce; int /*<<< orphan*/  keys; TYPE_1__ proposal; } ;
struct eap_ikev2_data {int keymat_ok; int /*<<< orphan*/  keymat; TYPE_2__ ikev2; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 scalar_t__ eap_ikev2_derive_keymat (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int eap_ikev2_server_keymat(struct eap_ikev2_data *data)
{
	if (eap_ikev2_derive_keymat(
		    data->ikev2.proposal.prf, &data->ikev2.keys,
		    data->ikev2.i_nonce, data->ikev2.i_nonce_len,
		    data->ikev2.r_nonce, data->ikev2.r_nonce_len,
		    data->keymat) < 0) {
		wpa_printf(MSG_DEBUG, "EAP-IKEV2: Failed to derive "
			   "key material");
		return -1;
	}
	data->keymat_ok = 1;
	return 0;
}