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
struct hmac_test {size_t data_len; int /*<<< orphan*/  hash; int /*<<< orphan*/  key_len; int /*<<< orphan*/  key; int /*<<< orphan*/ * data; } ;
typedef  int /*<<< orphan*/  hash ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (struct hmac_test*) ; 
 int /*<<< orphan*/  MSG_INFO ; 
 scalar_t__ hmac_sha256 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *) ; 
 int hmac_sha256_kdf (int /*<<< orphan*/ *,int,char*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 
 scalar_t__ hmac_sha256_vector (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/  const**,size_t*,int /*<<< orphan*/ *) ; 
 struct hmac_test* hmac_tests ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  os_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * os_malloc (int) ; 
 scalar_t__ os_memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sha256_prf (int /*<<< orphan*/ *,int,char*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sha256_vector (int,int /*<<< orphan*/  const**,size_t*,int /*<<< orphan*/ *) ; 
 int strlen (int /*<<< orphan*/ *) ; 
 struct hmac_test* tests ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int test_sha256(void)
{
	unsigned int i;
	u8 hash[32];
	const u8 *addr[2];
	size_t len[2];
	int errors = 0;
	u8 *key;

	for (i = 0; i < ARRAY_SIZE(tests); i++) {
		wpa_printf(MSG_INFO, "SHA256 test case %d:", i + 1);

		addr[0] = (u8 *) tests[i].data;
		len[0] = strlen(tests[i].data);
		sha256_vector(1, addr, len, hash);
		if (memcmp(hash, tests[i].hash, 32) != 0) {
			wpa_printf(MSG_INFO, " FAIL");
			errors++;
		} else
			wpa_printf(MSG_INFO, " OK");

		if (len[0]) {
			addr[0] = (u8 *) tests[i].data;
			len[0] = 1;
			addr[1] = (u8 *) tests[i].data + 1;
			len[1] = strlen(tests[i].data) - 1;
			sha256_vector(2, addr, len, hash);
			if (memcmp(hash, tests[i].hash, 32) != 0) {
				wpa_printf(MSG_INFO, " FAIL");
				errors++;
			} else
				wpa_printf(MSG_INFO, " OK");
		}
	}

	for (i = 0; i < ARRAY_SIZE(hmac_tests); i++) {
		const struct hmac_test *t = &hmac_tests[i];

		wpa_printf(MSG_INFO, "HMAC-SHA256 test case %d:", i + 1);

		if (hmac_sha256(t->key, t->key_len, t->data, t->data_len,
				hash) < 0 ||
		    os_memcmp(hash, t->hash, 32) != 0) {
			wpa_printf(MSG_INFO, " FAIL");
			errors++;
		} else
			wpa_printf(MSG_INFO, " OK");

		addr[0] = t->data;
		len[0] = t->data_len;
		if (hmac_sha256_vector(t->key, t->key_len, 1, addr, len,
				       hash) < 0 ||
		    os_memcmp(hash, t->hash, 32) != 0) {
			wpa_printf(MSG_INFO, " FAIL");
			errors++;
		} else
			wpa_printf(MSG_INFO, " OK");

		if (len[0]) {
			addr[0] = t->data;
			len[0] = 1;
			addr[1] = t->data + 1;
			len[1] = t->data_len - 1;
			if (hmac_sha256_vector(t->key, t->key_len, 2, addr, len,
					       hash) < 0 ||
			    os_memcmp(hash, t->hash, 32) != 0) {
				wpa_printf(MSG_INFO, " FAIL");
				errors++;
			} else
				wpa_printf(MSG_INFO, " OK");
		}
	}

	wpa_printf(MSG_INFO, "Test IEEE 802.11r KDF");
	sha256_prf((u8 *) "abc", 3, "KDF test", (u8 *) "data", 4,
		   hash, sizeof(hash));
	/* TODO: add proper test case for this */

	key = os_malloc(8161);
	if (key) {
#ifdef CONFIG_HMAC_SHA256_KDF
		int res;

		res = hmac_sha256_kdf((u8 *) "secret", 6, "label",
				      (u8 *) "seed", 4, key, 8160);
		if (res) {
			wpa_printf(MSG_INFO,
				   "Unexpected hmac_sha256_kdf(outlen=8160) failure");
			errors++;
		}

		res = hmac_sha256_kdf((u8 *) "secret", 6, "label",
				      (u8 *) "seed", 4, key, 8161);
		if (res == 0) {
			wpa_printf(MSG_INFO,
				   "Unexpected hmac_sha256_kdf(outlen=8161) success");
			errors++;
		}
#endif /* CONFIG_HMAC_SHA256_KDF */

		os_free(key);
	}

	if (!errors)
		wpa_printf(MSG_INFO, "SHA256 test cases passed");
	return errors;
}