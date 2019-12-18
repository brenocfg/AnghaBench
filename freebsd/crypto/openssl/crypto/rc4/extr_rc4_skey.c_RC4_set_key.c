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
struct TYPE_3__ {unsigned int* data; scalar_t__ y; scalar_t__ x; } ;
typedef  TYPE_1__ RC4_KEY ;
typedef  unsigned int RC4_INT ;

/* Variables and functions */
 int /*<<< orphan*/  SK_LOOP (unsigned int*,unsigned int) ; 

void RC4_set_key(RC4_KEY *key, int len, const unsigned char *data)
{
    register RC4_INT tmp;
    register int id1, id2;
    register RC4_INT *d;
    unsigned int i;

    d = &(key->data[0]);
    key->x = 0;
    key->y = 0;
    id1 = id2 = 0;

#define SK_LOOP(d,n) { \
                tmp=d[(n)]; \
                id2 = (data[id1] + tmp + id2) & 0xff; \
                if (++id1 == len) id1=0; \
                d[(n)]=d[id2]; \
                d[id2]=tmp; }

    for (i = 0; i < 256; i++)
        d[i] = i;
    for (i = 0; i < 256; i += 4) {
        SK_LOOP(d, i + 0);
        SK_LOOP(d, i + 1);
        SK_LOOP(d, i + 2);
        SK_LOOP(d, i + 3);
    }
}