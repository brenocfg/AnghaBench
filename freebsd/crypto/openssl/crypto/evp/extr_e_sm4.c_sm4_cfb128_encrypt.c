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
typedef  int /*<<< orphan*/  block128_f ;
typedef  int /*<<< orphan*/  SM4_KEY ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_cfb128_encrypt (unsigned char const*,unsigned char*,size_t,int /*<<< orphan*/  const*,unsigned char*,int*,int const,int /*<<< orphan*/ ) ; 
 scalar_t__ SM4_encrypt ; 

__attribute__((used)) static void sm4_cfb128_encrypt(const unsigned char *in, unsigned char *out,
                               size_t length, const SM4_KEY *key,
                               unsigned char *ivec, int *num, const int enc)
{
    CRYPTO_cfb128_encrypt(in, out, length, key, ivec, num, enc,
                          (block128_f)SM4_encrypt);
}