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
typedef  scalar_t__ BF_LONG ;
typedef  int /*<<< orphan*/  BF_KEY ;

/* Variables and functions */
 int /*<<< orphan*/  BF_decrypt (scalar_t__*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  BF_encrypt (scalar_t__*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  l2n (scalar_t__,unsigned char*) ; 
 int /*<<< orphan*/  n2l (unsigned char const*,scalar_t__) ; 

void BF_ecb_encrypt(const unsigned char *in, unsigned char *out,
                    const BF_KEY *key, int encrypt)
{
    BF_LONG l, d[2];

    n2l(in, l);
    d[0] = l;
    n2l(in, l);
    d[1] = l;
    if (encrypt)
        BF_encrypt(d, key);
    else
        BF_decrypt(d, key);
    l = d[0];
    l2n(l, out);
    l = d[1];
    l2n(l, out);
    l = d[0] = d[1] = 0;
}