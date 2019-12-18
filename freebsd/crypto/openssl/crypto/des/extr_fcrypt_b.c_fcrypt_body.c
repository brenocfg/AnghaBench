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
typedef  int DES_LONG ;

/* Variables and functions */
 int /*<<< orphan*/  D_ENCRYPT (int,int,int) ; 
 int /*<<< orphan*/  PERM_OP (int,int,int,int,int) ; 
 int ROTATE (int,int) ; 

void fcrypt_body(DES_LONG *out, DES_key_schedule *ks, DES_LONG Eswap0,
                 DES_LONG Eswap1)
{
    register DES_LONG l, r, t, u;
    register DES_LONG *s;
    register int j;
    register DES_LONG E0, E1;

    l = 0;
    r = 0;

    s = (DES_LONG *)ks;
    E0 = Eswap0;
    E1 = Eswap1;

    for (j = 0; j < 25; j++) {
        D_ENCRYPT(l, r, 0);     /* 1 */
        D_ENCRYPT(r, l, 2);     /* 2 */
        D_ENCRYPT(l, r, 4);     /* 3 */
        D_ENCRYPT(r, l, 6);     /* 4 */
        D_ENCRYPT(l, r, 8);     /* 5 */
        D_ENCRYPT(r, l, 10);    /* 6 */
        D_ENCRYPT(l, r, 12);    /* 7 */
        D_ENCRYPT(r, l, 14);    /* 8 */
        D_ENCRYPT(l, r, 16);    /* 9 */
        D_ENCRYPT(r, l, 18);    /* 10 */
        D_ENCRYPT(l, r, 20);    /* 11 */
        D_ENCRYPT(r, l, 22);    /* 12 */
        D_ENCRYPT(l, r, 24);    /* 13 */
        D_ENCRYPT(r, l, 26);    /* 14 */
        D_ENCRYPT(l, r, 28);    /* 15 */
        D_ENCRYPT(r, l, 30);    /* 16 */
        t = l;
        l = r;
        r = t;
    }
    l = ROTATE(l, 3) & 0xffffffffL;
    r = ROTATE(r, 3) & 0xffffffffL;

    PERM_OP(l, r, t,  1, 0x55555555L);
    PERM_OP(r, l, t,  8, 0x00ff00ffL);
    PERM_OP(l, r, t,  2, 0x33333333L);
    PERM_OP(r, l, t, 16, 0x0000ffffL);
    PERM_OP(l, r, t,  4, 0x0f0f0f0fL);

    out[0] = r;
    out[1] = l;
}