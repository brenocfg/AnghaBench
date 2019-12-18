#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {unsigned long* r; unsigned long* h; scalar_t__ final; } ;
typedef  TYPE_1__ poly1305_state_internal_t ;

/* Variables and functions */
 int LOAD32_LE (unsigned char const*) ; 
 unsigned long long poly1305_block_size ; 

__attribute__((used)) static void
poly1305_blocks(poly1305_state_internal_t *st, const unsigned char *m,
                unsigned long long bytes)
{
    const unsigned long hibit = (st->final) ? 0UL : (1UL << 24); /* 1 << 128 */
    unsigned long       r0, r1, r2, r3, r4;
    unsigned long       s1, s2, s3, s4;
    unsigned long       h0, h1, h2, h3, h4;
    unsigned long long  d0, d1, d2, d3, d4;
    unsigned long       c;

    r0 = st->r[0];
    r1 = st->r[1];
    r2 = st->r[2];
    r3 = st->r[3];
    r4 = st->r[4];

    s1 = r1 * 5;
    s2 = r2 * 5;
    s3 = r3 * 5;
    s4 = r4 * 5;

    h0 = st->h[0];
    h1 = st->h[1];
    h2 = st->h[2];
    h3 = st->h[3];
    h4 = st->h[4];

    while (bytes >= poly1305_block_size) {
        /* h += m[i] */
        h0 += (LOAD32_LE(m + 0)) & 0x3ffffff;
        h1 += (LOAD32_LE(m + 3) >> 2) & 0x3ffffff;
        h2 += (LOAD32_LE(m + 6) >> 4) & 0x3ffffff;
        h3 += (LOAD32_LE(m + 9) >> 6) & 0x3ffffff;
        h4 += (LOAD32_LE(m + 12) >> 8) | hibit;

        /* h *= r */
        d0 = ((unsigned long long) h0 * r0) + ((unsigned long long) h1 * s4) +
             ((unsigned long long) h2 * s3) + ((unsigned long long) h3 * s2) +
             ((unsigned long long) h4 * s1);
        d1 = ((unsigned long long) h0 * r1) + ((unsigned long long) h1 * r0) +
             ((unsigned long long) h2 * s4) + ((unsigned long long) h3 * s3) +
             ((unsigned long long) h4 * s2);
        d2 = ((unsigned long long) h0 * r2) + ((unsigned long long) h1 * r1) +
             ((unsigned long long) h2 * r0) + ((unsigned long long) h3 * s4) +
             ((unsigned long long) h4 * s3);
        d3 = ((unsigned long long) h0 * r3) + ((unsigned long long) h1 * r2) +
             ((unsigned long long) h2 * r1) + ((unsigned long long) h3 * r0) +
             ((unsigned long long) h4 * s4);
        d4 = ((unsigned long long) h0 * r4) + ((unsigned long long) h1 * r3) +
             ((unsigned long long) h2 * r2) + ((unsigned long long) h3 * r1) +
             ((unsigned long long) h4 * r0);

        /* (partial) h %= p */
        c  = (unsigned long) (d0 >> 26);
        h0 = (unsigned long) d0 & 0x3ffffff;
        d1 += c;
        c  = (unsigned long) (d1 >> 26);
        h1 = (unsigned long) d1 & 0x3ffffff;
        d2 += c;
        c  = (unsigned long) (d2 >> 26);
        h2 = (unsigned long) d2 & 0x3ffffff;
        d3 += c;
        c  = (unsigned long) (d3 >> 26);
        h3 = (unsigned long) d3 & 0x3ffffff;
        d4 += c;
        c  = (unsigned long) (d4 >> 26);
        h4 = (unsigned long) d4 & 0x3ffffff;
        h0 += c * 5;
        c  = (h0 >> 26);
        h0 = h0 & 0x3ffffff;
        h1 += c;

        m += poly1305_block_size;
        bytes -= poly1305_block_size;
    }

    st->h[0] = h0;
    st->h[1] = h1;
    st->h[2] = h2;
    st->h[3] = h3;
    st->h[4] = h4;
}