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
typedef  size_t u8 ;
typedef  int u64 ;
typedef  scalar_t__ u32 ;
struct TYPE_3__ {int hi; int lo; } ;
typedef  TYPE_1__ u128 ;

/* Variables and functions */
 int BSWAP8 (int) ; 
 int /*<<< orphan*/  PUTU32 (size_t*,scalar_t__) ; 
 int* rem_4bit ; 

__attribute__((used)) static void gcm_gmult_4bit(u64 Xi[2], const u128 Htable[16])
{
    u128 Z;
    int cnt = 15;
    size_t rem, nlo, nhi;
    const union {
        long one;
        char little;
    } is_endian = { 1 };

    nlo = ((const u8 *)Xi)[15];
    nhi = nlo >> 4;
    nlo &= 0xf;

    Z.hi = Htable[nlo].hi;
    Z.lo = Htable[nlo].lo;

    while (1) {
        rem = (size_t)Z.lo & 0xf;
        Z.lo = (Z.hi << 60) | (Z.lo >> 4);
        Z.hi = (Z.hi >> 4);
        if (sizeof(size_t) == 8)
            Z.hi ^= rem_4bit[rem];
        else
            Z.hi ^= (u64)rem_4bit[rem] << 32;

        Z.hi ^= Htable[nhi].hi;
        Z.lo ^= Htable[nhi].lo;

        if (--cnt < 0)
            break;

        nlo = ((const u8 *)Xi)[cnt];
        nhi = nlo >> 4;
        nlo &= 0xf;

        rem = (size_t)Z.lo & 0xf;
        Z.lo = (Z.hi << 60) | (Z.lo >> 4);
        Z.hi = (Z.hi >> 4);
        if (sizeof(size_t) == 8)
            Z.hi ^= rem_4bit[rem];
        else
            Z.hi ^= (u64)rem_4bit[rem] << 32;

        Z.hi ^= Htable[nlo].hi;
        Z.lo ^= Htable[nlo].lo;
    }

    if (is_endian.little) {
#  ifdef BSWAP8
        Xi[0] = BSWAP8(Z.hi);
        Xi[1] = BSWAP8(Z.lo);
#  else
        u8 *p = (u8 *)Xi;
        u32 v;
        v = (u32)(Z.hi >> 32);
        PUTU32(p, v);
        v = (u32)(Z.hi);
        PUTU32(p + 4, v);
        v = (u32)(Z.lo >> 32);
        PUTU32(p + 8, v);
        v = (u32)(Z.lo);
        PUTU32(p + 12, v);
#  endif
    } else {
        Xi[0] = Z.hi;
        Xi[1] = Z.lo;
    }
}