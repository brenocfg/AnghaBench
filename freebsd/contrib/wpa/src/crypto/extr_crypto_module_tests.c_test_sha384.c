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
struct hmac_test {scalar_t__* hash384; int* data; size_t data_len; int /*<<< orphan*/  key_len; int /*<<< orphan*/  key; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (struct hmac_test*) ; 
 int /*<<< orphan*/  MSG_INFO ; 
 scalar_t__ hmac_sha384 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,size_t,int*) ; 
 scalar_t__ hmac_sha384_vector (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int const**,size_t*,int*) ; 
 struct hmac_test* hmac_tests ; 
 scalar_t__ os_memcmp (int*,int const*,int) ; 
 scalar_t__ sha384_vector (int,int const**,size_t*,int*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int test_sha384(void)
{
#ifdef CONFIG_SHA384
	unsigned int i;
	u8 hash[48];
	const u8 *addr[2];
	size_t len[2];
	int errors = 0;
	const char *data = "hello";
	const u8 hash_res[] = {
		0x59, 0xe1, 0x74, 0x87, 0x77, 0x44, 0x8c, 0x69,
		0xde, 0x6b, 0x80, 0x0d, 0x7a, 0x33, 0xbb, 0xfb,
		0x9f, 0xf1, 0xb4, 0x63, 0xe4, 0x43, 0x54, 0xc3,
		0x55, 0x3b, 0xcd, 0xb9, 0xc6, 0x66, 0xfa, 0x90,
		0x12, 0x5a, 0x3c, 0x79, 0xf9, 0x03, 0x97, 0xbd,
		0xf5, 0xf6, 0xa1, 0x3d, 0xe8, 0x28, 0x68, 0x4f
	};

	addr[0] = (const u8 *) data;
	len[0] = 5;
	if (sha384_vector(1, addr, len, hash) < 0 ||
	    os_memcmp(hash, hash_res, 48) != 0) {
		wpa_printf(MSG_INFO, "SHA384 test case 1: FAIL");
		errors++;
	} else {
		wpa_printf(MSG_INFO, "SHA384 test case 1: OK");
	}

	addr[0] = (const u8 *) data;
	len[0] = 4;
	addr[1] = (const u8 *) data + 4;
	len[1] = 1;
	if (sha384_vector(2, addr, len, hash) < 0 ||
	    os_memcmp(hash, hash_res, 48) != 0) {
		wpa_printf(MSG_INFO, "SHA384 test case 2: FAIL");
		errors++;
	} else {
		wpa_printf(MSG_INFO, "SHA384 test case 2: OK");
	}

	for (i = 0; i < ARRAY_SIZE(hmac_tests); i++) {
		const struct hmac_test *t = &hmac_tests[i];

		if (t->hash384[0] == 0 && t->hash384[1] == 0 &&
		    t->hash384[2] == 0 && t->hash384[3] == 0)
			continue;
		wpa_printf(MSG_INFO, "HMAC-SHA384 test case %d:", i + 1);

		if (hmac_sha384(t->key, t->key_len, t->data, t->data_len,
				hash) < 0 ||
		    os_memcmp(hash, t->hash384, 48) != 0) {
			wpa_printf(MSG_INFO, " FAIL");
			errors++;
		} else
			wpa_printf(MSG_INFO, " OK");

		addr[0] = t->data;
		len[0] = t->data_len;
		if (hmac_sha384_vector(t->key, t->key_len, 1, addr, len,
				       hash) < 0 ||
		    os_memcmp(hash, t->hash384, 48) != 0) {
			wpa_printf(MSG_INFO, " FAIL");
			errors++;
		} else
			wpa_printf(MSG_INFO, " OK");

		if (len[0]) {
			addr[0] = t->data;
			len[0] = 1;
			addr[1] = t->data + 1;
			len[1] = t->data_len - 1;
			if (hmac_sha384_vector(t->key, t->key_len, 2, addr, len,
					       hash) < 0 ||
			    os_memcmp(hash, t->hash384, 48) != 0) {
				wpa_printf(MSG_INFO, " FAIL");
				errors++;
			} else
				wpa_printf(MSG_INFO, " OK");
		}
	}

	if (!errors)
		wpa_printf(MSG_INFO, "SHA384 test cases passed");
	return errors;
#else /* CONFIG_SHA384 */
	return 0;
#endif /* CONFIG_SHA384 */
}