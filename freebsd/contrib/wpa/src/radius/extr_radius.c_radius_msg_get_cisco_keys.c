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
struct radius_msg {TYPE_1__* hdr; } ;
struct radius_ms_mppe_keys {int /*<<< orphan*/  recv_len; int /*<<< orphan*/  recv; } ;
struct TYPE_2__ {int /*<<< orphan*/  authenticator; } ;

/* Variables and functions */
 int /*<<< orphan*/  RADIUS_CISCO_AV_PAIR ; 
 int /*<<< orphan*/  RADIUS_VENDOR_ID_CISCO ; 
 int /*<<< orphan*/  decrypt_ms_key (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_free (int /*<<< orphan*/ *) ; 
 scalar_t__ os_memcmp (int /*<<< orphan*/ *,char*,int) ; 
 struct radius_ms_mppe_keys* os_zalloc (int) ; 
 int /*<<< orphan*/ * radius_msg_get_vendor_attr (struct radius_msg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t*) ; 

struct radius_ms_mppe_keys *
radius_msg_get_cisco_keys(struct radius_msg *msg, struct radius_msg *sent_msg,
			  const u8 *secret, size_t secret_len)
{
	u8 *key;
	size_t keylen;
	struct radius_ms_mppe_keys *keys;

	if (msg == NULL || sent_msg == NULL)
		return NULL;

	keys = os_zalloc(sizeof(*keys));
	if (keys == NULL)
		return NULL;

	key = radius_msg_get_vendor_attr(msg, RADIUS_VENDOR_ID_CISCO,
					 RADIUS_CISCO_AV_PAIR, &keylen);
	if (key && keylen == 51 &&
	    os_memcmp(key, "leap:session-key=", 17) == 0) {
		keys->recv = decrypt_ms_key(key + 17, keylen - 17,
					    sent_msg->hdr->authenticator,
					    secret, secret_len,
					    &keys->recv_len);
	}
	os_free(key);

	return keys;
}