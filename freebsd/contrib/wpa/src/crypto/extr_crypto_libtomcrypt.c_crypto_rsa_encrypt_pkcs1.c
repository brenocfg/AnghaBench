#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_4__ {int /*<<< orphan*/  N; } ;
typedef  TYPE_1__ rsa_key ;

/* Variables and functions */
 int CRYPT_OK ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  error_to_string (int) ; 
 unsigned long mp_unsigned_bin_size (int /*<<< orphan*/ ) ; 
 scalar_t__ pkcs1_generate_encryption_block (int,unsigned long,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ *,size_t*) ; 
 int rsa_exptmod (int /*<<< orphan*/ *,unsigned long,int /*<<< orphan*/ *,unsigned long*,int,TYPE_1__*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int crypto_rsa_encrypt_pkcs1(int block_type, rsa_key *key, int key_type,
				    const u8 *in, size_t inlen,
				    u8 *out, size_t *outlen)
{
	unsigned long len, modlen;
	int res;

	modlen = mp_unsigned_bin_size(key->N);

	if (pkcs1_generate_encryption_block(block_type, modlen, in, inlen,
					    out, outlen) < 0)
		return -1;

	len = *outlen;
	res = rsa_exptmod(out, modlen, out, &len, key_type, key);
	if (res != CRYPT_OK) {
		wpa_printf(MSG_DEBUG, "LibTomCrypt: rsa_exptmod failed: %s",
			   error_to_string(res));
		return -1;
	}
	*outlen = len;

	return 0;
}