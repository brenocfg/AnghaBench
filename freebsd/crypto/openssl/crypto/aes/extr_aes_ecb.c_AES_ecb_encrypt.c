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
typedef  int /*<<< orphan*/  AES_KEY ;

/* Variables and functions */
 int const AES_DECRYPT ; 
 int const AES_ENCRYPT ; 
 int /*<<< orphan*/  AES_decrypt (unsigned char const*,unsigned char*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  AES_encrypt (unsigned char const*,unsigned char*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  assert (int) ; 

void AES_ecb_encrypt(const unsigned char *in, unsigned char *out,
                     const AES_KEY *key, const int enc)
{

    assert(in && out && key);
    assert((AES_ENCRYPT == enc) || (AES_DECRYPT == enc));

    if (AES_ENCRYPT == enc)
        AES_encrypt(in, out, key);
    else
        AES_decrypt(in, out, key);
}