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
typedef  int /*<<< orphan*/  DES_key_schedule ;
typedef  unsigned char* DES_cblock ;
typedef  scalar_t__ DES_LONG ;

/* Variables and functions */
 int /*<<< orphan*/  DES_ENCRYPT ; 
 int /*<<< orphan*/  DES_encrypt1 (scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  c2l (unsigned char*,scalar_t__) ; 
 int /*<<< orphan*/  l2c (scalar_t__,unsigned char*) ; 

void DES_ofb64_encrypt(register const unsigned char *in,
                       register unsigned char *out, long length,
                       DES_key_schedule *schedule, DES_cblock *ivec, int *num)
{
    register DES_LONG v0, v1, t;
    register int n = *num;
    register long l = length;
    DES_cblock d;
    register unsigned char *dp;
    DES_LONG ti[2];
    unsigned char *iv;
    int save = 0;

    iv = &(*ivec)[0];
    c2l(iv, v0);
    c2l(iv, v1);
    ti[0] = v0;
    ti[1] = v1;
    dp = d;
    l2c(v0, dp);
    l2c(v1, dp);
    while (l--) {
        if (n == 0) {
            DES_encrypt1(ti, schedule, DES_ENCRYPT);
            dp = d;
            t = ti[0];
            l2c(t, dp);
            t = ti[1];
            l2c(t, dp);
            save++;
        }
        *(out++) = *(in++) ^ d[n];
        n = (n + 1) & 0x07;
    }
    if (save) {
        v0 = ti[0];
        v1 = ti[1];
        iv = &(*ivec)[0];
        l2c(v0, iv);
        l2c(v1, iv);
    }
    t = v0 = v1 = ti[0] = ti[1] = 0;
    *num = n;
}