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
typedef  int /*<<< orphan*/  RSA ;
typedef  int /*<<< orphan*/  EVP_MD ;

/* Variables and functions */
 int RSA_padding_add_PKCS1_PSS_mgf1 (int /*<<< orphan*/ *,unsigned char*,unsigned char const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int) ; 

int RSA_padding_add_PKCS1_PSS(RSA *rsa, unsigned char *EM,
                              const unsigned char *mHash,
                              const EVP_MD *Hash, int sLen)
{
    return RSA_padding_add_PKCS1_PSS_mgf1(rsa, EM, mHash, Hash, NULL, sLen);
}