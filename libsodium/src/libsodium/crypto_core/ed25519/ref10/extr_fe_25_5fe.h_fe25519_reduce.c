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
typedef  int uint32_t ;
typedef  int int32_t ;
typedef  int* fe25519 ;

/* Variables and functions */

__attribute__((used)) static void
fe25519_reduce(fe25519 h, const fe25519 f)
{
    int32_t h0 = f[0];
    int32_t h1 = f[1];
    int32_t h2 = f[2];
    int32_t h3 = f[3];
    int32_t h4 = f[4];
    int32_t h5 = f[5];
    int32_t h6 = f[6];
    int32_t h7 = f[7];
    int32_t h8 = f[8];
    int32_t h9 = f[9];

    int32_t q;
    int32_t carry0, carry1, carry2, carry3, carry4, carry5, carry6, carry7, carry8, carry9;

    q = (19 * h9 + ((uint32_t) 1L << 24)) >> 25;
    q = (h0 + q) >> 26;
    q = (h1 + q) >> 25;
    q = (h2 + q) >> 26;
    q = (h3 + q) >> 25;
    q = (h4 + q) >> 26;
    q = (h5 + q) >> 25;
    q = (h6 + q) >> 26;
    q = (h7 + q) >> 25;
    q = (h8 + q) >> 26;
    q = (h9 + q) >> 25;

    /* Goal: Output h-(2^255-19)q, which is between 0 and 2^255-20. */
    h0 += 19 * q;
    /* Goal: Output h-2^255 q, which is between 0 and 2^255-20. */

    carry0 = h0 >> 26;
    h1 += carry0;
    h0 -= carry0 * ((uint32_t) 1L << 26);
    carry1 = h1 >> 25;
    h2 += carry1;
    h1 -= carry1 * ((uint32_t) 1L << 25);
    carry2 = h2 >> 26;
    h3 += carry2;
    h2 -= carry2 * ((uint32_t) 1L << 26);
    carry3 = h3 >> 25;
    h4 += carry3;
    h3 -= carry3 * ((uint32_t) 1L << 25);
    carry4 = h4 >> 26;
    h5 += carry4;
    h4 -= carry4 * ((uint32_t) 1L << 26);
    carry5 = h5 >> 25;
    h6 += carry5;
    h5 -= carry5 * ((uint32_t) 1L << 25);
    carry6 = h6 >> 26;
    h7 += carry6;
    h6 -= carry6 * ((uint32_t) 1L << 26);
    carry7 = h7 >> 25;
    h8 += carry7;
    h7 -= carry7 * ((uint32_t) 1L << 25);
    carry8 = h8 >> 26;
    h9 += carry8;
    h8 -= carry8 * ((uint32_t) 1L << 26);
    carry9 = h9 >> 25;
    h9 -= carry9 * ((uint32_t) 1L << 25);

    h[0] = h0;
    h[1] = h1;
    h[2] = h2;
    h[3] = h3;
    h[4] = h4;
    h[5] = h5;
    h[6] = h6;
    h[7] = h7;
    h[8] = h8;
    h[9] = h9;
}