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

/* Variables and functions */
 scalar_t__ CRYPTO_MAX_ALG_NAME ; 
 int EINVAL ; 
 int ENOPKG ; 
 scalar_t__ snprintf (char*,scalar_t__,char*,char const*) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

__attribute__((used)) static int determine_akcipher(const char *encoding, const char *hash_algo,
			      char alg_name[CRYPTO_MAX_ALG_NAME])
{
	if (strcmp(encoding, "pkcs1") == 0) {
		if (!hash_algo) {
			strcpy(alg_name, "pkcs1pad(rsa)");
			return 0;
		}

		if (snprintf(alg_name, CRYPTO_MAX_ALG_NAME, "pkcs1pad(rsa,%s)",
			     hash_algo) >= CRYPTO_MAX_ALG_NAME)
			return -EINVAL;

		return 0;
	}

	if (strcmp(encoding, "raw") == 0) {
		strcpy(alg_name, "rsa");
		return 0;
	}

	return -ENOPKG;
}