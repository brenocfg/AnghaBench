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
typedef  int /*<<< orphan*/  EVP_MD ;

/* Variables and functions */
 int /*<<< orphan*/  HMAC (int /*<<< orphan*/  const*,unsigned char const*,size_t,unsigned char const*,size_t,unsigned char*,unsigned int*) ; 

__attribute__((used)) static unsigned char *HKDF_Extract(const EVP_MD *evp_md,
                                   const unsigned char *salt, size_t salt_len,
                                   const unsigned char *key, size_t key_len,
                                   unsigned char *prk, size_t *prk_len)
{
    unsigned int tmp_len;

    if (!HMAC(evp_md, salt, salt_len, key, key_len, prk, &tmp_len))
        return NULL;

    *prk_len = tmp_len;
    return prk;
}