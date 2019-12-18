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
typedef  unsigned char* const_DES_cblock ;
typedef  int /*<<< orphan*/  DES_key_schedule ;
typedef  unsigned char* DES_cblock ;
typedef  int /*<<< orphan*/  DES_LONG ;

/* Variables and functions */
 int /*<<< orphan*/  DES_decrypt3 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DES_encrypt3 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  c2l (unsigned char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2c (int /*<<< orphan*/ ,unsigned char*) ; 

void DES_ecb3_encrypt(const_DES_cblock *input, DES_cblock *output,
                      DES_key_schedule *ks1, DES_key_schedule *ks2,
                      DES_key_schedule *ks3, int enc)
{
    register DES_LONG l0, l1;
    DES_LONG ll[2];
    const unsigned char *in = &(*input)[0];
    unsigned char *out = &(*output)[0];

    c2l(in, l0);
    c2l(in, l1);
    ll[0] = l0;
    ll[1] = l1;
    if (enc)
        DES_encrypt3(ll, ks1, ks2, ks3);
    else
        DES_decrypt3(ll, ks1, ks2, ks3);
    l0 = ll[0];
    l1 = ll[1];
    l2c(l0, out);
    l2c(l1, out);
}