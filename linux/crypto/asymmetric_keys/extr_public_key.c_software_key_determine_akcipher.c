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
struct public_key {char* pkey_algo; } ;

/* Variables and functions */
 int CRYPTO_MAX_ALG_NAME ; 
 int EINVAL ; 
 int ENOPKG ; 
 int snprintf (char*,int,char*,char*,...) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

__attribute__((used)) static
int software_key_determine_akcipher(const char *encoding,
				    const char *hash_algo,
				    const struct public_key *pkey,
				    char alg_name[CRYPTO_MAX_ALG_NAME])
{
	int n;

	if (strcmp(encoding, "pkcs1") == 0) {
		/* The data wangled by the RSA algorithm is typically padded
		 * and encoded in some manner, such as EMSA-PKCS1-1_5 [RFC3447
		 * sec 8.2].
		 */
		if (!hash_algo)
			n = snprintf(alg_name, CRYPTO_MAX_ALG_NAME,
				     "pkcs1pad(%s)",
				     pkey->pkey_algo);
		else
			n = snprintf(alg_name, CRYPTO_MAX_ALG_NAME,
				     "pkcs1pad(%s,%s)",
				     pkey->pkey_algo, hash_algo);
		return n >= CRYPTO_MAX_ALG_NAME ? -EINVAL : 0;
	}

	if (strcmp(encoding, "raw") == 0) {
		strcpy(alg_name, pkey->pkey_algo);
		return 0;
	}

	return -ENOPKG;
}