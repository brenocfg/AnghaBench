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
typedef  int /*<<< orphan*/  CAMELLIA_KEY ;

/* Variables and functions */
 int const CAMELLIA_ENCRYPT ; 
 int /*<<< orphan*/  Camellia_decrypt (unsigned char const*,unsigned char*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  Camellia_encrypt (unsigned char const*,unsigned char*,int /*<<< orphan*/  const*) ; 

void Camellia_ecb_encrypt(const unsigned char *in, unsigned char *out,
                          const CAMELLIA_KEY *key, const int enc)
{
    if (CAMELLIA_ENCRYPT == enc)
        Camellia_encrypt(in, out, key);
    else
        Camellia_decrypt(in, out, key);
}