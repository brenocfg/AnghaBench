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
typedef  int /*<<< orphan*/  u8 ;
struct eap_sm {int dummy; } ;
struct TYPE_2__ {int i_nonce_len; int r_nonce_len; int /*<<< orphan*/  r_nonce; int /*<<< orphan*/  i_nonce; } ;
struct eap_ikev2_data {scalar_t__ state; TYPE_1__ ikev2; int /*<<< orphan*/  keymat_ok; } ;

/* Variables and functions */
 scalar_t__ DONE ; 
 int /*<<< orphan*/  EAP_TYPE_IKEV2 ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/ * os_malloc (size_t) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static u8 * eap_ikev2_get_session_id(struct eap_sm *sm, void *priv, size_t *len)
{
	struct eap_ikev2_data *data = priv;
	u8 *sid;
	size_t sid_len;
	size_t offset;

	if (data->state != DONE || !data->keymat_ok)
		return NULL;

	sid_len = 1 + data->ikev2.i_nonce_len + data->ikev2.r_nonce_len;
	sid = os_malloc(sid_len);
	if (sid) {
		offset = 0;
		sid[offset] = EAP_TYPE_IKEV2;
		offset++;
		os_memcpy(sid + offset, data->ikev2.i_nonce,
			  data->ikev2.i_nonce_len);
		offset += data->ikev2.i_nonce_len;
		os_memcpy(sid + offset, data->ikev2.r_nonce,
			  data->ikev2.r_nonce_len);
		*len = sid_len;
		wpa_hexdump(MSG_DEBUG, "EAP-IKEV2: Derived Session-Id",
			    sid, sid_len);
	}

	return sid;
}