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
struct TYPE_3__ {int /*<<< orphan*/ * data; } ;
typedef  TYPE_1__ RC2_KEY ;
typedef  int /*<<< orphan*/  RC2_INT ;

/* Variables and functions */
 unsigned int* key_table ; 

void RC2_set_key(RC2_KEY *key, int len, const unsigned char *data, int bits)
{
    int i, j;
    unsigned char *k;
    RC2_INT *ki;
    unsigned int c, d;

    k = (unsigned char *)&(key->data[0]);
    *k = 0;                     /* for if there is a zero length key */

    if (len > 128)
        len = 128;
    if (bits <= 0)
        bits = 1024;
    if (bits > 1024)
        bits = 1024;

    for (i = 0; i < len; i++)
        k[i] = data[i];

    /* expand table */
    d = k[len - 1];
    j = 0;
    for (i = len; i < 128; i++, j++) {
        d = key_table[(k[j] + d) & 0xff];
        k[i] = d;
    }

    /* hmm.... key reduction to 'bits' bits */

    j = (bits + 7) >> 3;
    i = 128 - j;
    c = (0xff >> (-bits & 0x07));

    d = key_table[k[i] & c];
    k[i] = d;
    while (i--) {
        d = key_table[k[i + j] ^ d];
        k[i] = d;
    }

    /* copy from bytes into RC2_INT's */
    ki = &(key->data[63]);
    for (i = 127; i >= 0; i -= 2)
        *(ki--) = ((k[i] << 8) | k[i - 1]) & 0xffff;
}