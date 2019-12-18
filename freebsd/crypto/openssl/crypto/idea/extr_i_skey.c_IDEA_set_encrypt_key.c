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
struct TYPE_3__ {int** data; } ;
typedef  TYPE_1__ IDEA_KEY_SCHEDULE ;
typedef  int IDEA_INT ;

/* Variables and functions */
 int /*<<< orphan*/  n2s (unsigned char const*,int) ; 

void IDEA_set_encrypt_key(const unsigned char *key, IDEA_KEY_SCHEDULE *ks)
{
    int i;
    register IDEA_INT *kt, *kf, r0, r1, r2;

    kt = &(ks->data[0][0]);
    n2s(key, kt[0]);
    n2s(key, kt[1]);
    n2s(key, kt[2]);
    n2s(key, kt[3]);
    n2s(key, kt[4]);
    n2s(key, kt[5]);
    n2s(key, kt[6]);
    n2s(key, kt[7]);

    kf = kt;
    kt += 8;
    for (i = 0; i < 6; i++) {
        r2 = kf[1];
        r1 = kf[2];
        *(kt++) = ((r2 << 9) | (r1 >> 7)) & 0xffff;
        r0 = kf[3];
        *(kt++) = ((r1 << 9) | (r0 >> 7)) & 0xffff;
        r1 = kf[4];
        *(kt++) = ((r0 << 9) | (r1 >> 7)) & 0xffff;
        r0 = kf[5];
        *(kt++) = ((r1 << 9) | (r0 >> 7)) & 0xffff;
        r1 = kf[6];
        *(kt++) = ((r0 << 9) | (r1 >> 7)) & 0xffff;
        r0 = kf[7];
        *(kt++) = ((r1 << 9) | (r0 >> 7)) & 0xffff;
        r1 = kf[0];
        if (i >= 5)
            break;
        *(kt++) = ((r0 << 9) | (r1 >> 7)) & 0xffff;
        *(kt++) = ((r1 << 9) | (r2 >> 7)) & 0xffff;
        kf += 8;
    }
}