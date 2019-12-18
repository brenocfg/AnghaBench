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
struct eap_fast_pac {int /*<<< orphan*/  pac_key; } ;

/* Variables and functions */
 size_t EAP_FAST_PAC_KEY_LEN ; 
 int /*<<< orphan*/ * eap_fast_parse_hex (char*,size_t*) ; 
 int /*<<< orphan*/  os_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static const char * eap_fast_parse_pac_key(struct eap_fast_pac *pac, char *pos)
{
	u8 *key;
	size_t key_len;

	key = eap_fast_parse_hex(pos, &key_len);
	if (key == NULL || key_len != EAP_FAST_PAC_KEY_LEN) {
		os_free(key);
		return "Invalid PAC-Key";
	}

	os_memcpy(pac->pac_key, key, EAP_FAST_PAC_KEY_LEN);
	os_free(key);

	return NULL;
}