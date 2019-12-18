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
typedef  size_t u16 ;
struct wpabuf {int dummy; } ;
struct nai_realm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 size_t WPA_GET_LE16 (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  nai_realm_free (struct nai_realm*,size_t) ; 
 int /*<<< orphan*/ * nai_realm_parse_realm (struct nai_realm*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 struct nai_realm* os_calloc (size_t,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,size_t,...) ; 
 int /*<<< orphan*/ * wpabuf_head_u8 (struct wpabuf*) ; 
 size_t wpabuf_len (struct wpabuf*) ; 

__attribute__((used)) static struct nai_realm * nai_realm_parse(struct wpabuf *anqp, u16 *count)
{
	struct nai_realm *realm;
	const u8 *pos, *end;
	u16 i, num;
	size_t left;

	if (anqp == NULL)
		return NULL;
	left = wpabuf_len(anqp);
	if (left < 2)
		return NULL;

	pos = wpabuf_head_u8(anqp);
	end = pos + left;
	num = WPA_GET_LE16(pos);
	wpa_printf(MSG_DEBUG, "NAI Realm Count: %u", num);
	pos += 2;
	left -= 2;

	if (num > left / 5) {
		wpa_printf(MSG_DEBUG, "Invalid NAI Realm Count %u - not "
			   "enough data (%u octets) for that many realms",
			   num, (unsigned int) left);
		return NULL;
	}

	realm = os_calloc(num, sizeof(struct nai_realm));
	if (realm == NULL)
		return NULL;

	for (i = 0; i < num; i++) {
		pos = nai_realm_parse_realm(&realm[i], pos, end);
		if (pos == NULL) {
			nai_realm_free(realm, num);
			return NULL;
		}
	}

	*count = num;
	return realm;
}