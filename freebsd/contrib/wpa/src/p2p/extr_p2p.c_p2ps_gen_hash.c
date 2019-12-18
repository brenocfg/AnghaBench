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
struct p2p_data {int /*<<< orphan*/ * wild_card_hash; } ;
typedef  int /*<<< orphan*/  str_buf ;

/* Variables and functions */
 int /*<<< orphan*/  P2PS_HASH_LEN ; 
 int SHA256_MAC_LEN ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 size_t os_strlen (char const*) ; 
 scalar_t__ sha256_vector (int,int /*<<< orphan*/  const**,size_t*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int p2ps_gen_hash(struct p2p_data *p2p, const char *str, u8 *hash)
{
	u8 buf[SHA256_MAC_LEN];
	char str_buf[256];
	const u8 *adv_array;
	size_t i, adv_len;

	if (!str || !hash)
		return 0;

	if (!str[0]) {
		os_memcpy(hash, p2p->wild_card_hash, P2PS_HASH_LEN);
		return 1;
	}

	adv_array = (u8 *) str_buf;
	adv_len = os_strlen(str);
	if (adv_len >= sizeof(str_buf))
		return 0;

	for (i = 0; i < adv_len; i++) {
		if (str[i] >= 'A' && str[i] <= 'Z')
			str_buf[i] = str[i] - 'A' + 'a';
		else
			str_buf[i] = str[i];
	}

	if (sha256_vector(1, &adv_array, &adv_len, buf))
		return 0;

	os_memcpy(hash, buf, P2PS_HASH_LEN);
	return 1;
}