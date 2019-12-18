#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  void* u64 ;
struct TYPE_4__ {int hi; int lo; } ;
typedef  TYPE_1__ u128 ;

/* Variables and functions */
 int /*<<< orphan*/  REDUCE1BIT (TYPE_1__) ; 

__attribute__((used)) static void gcm_init_4bit(u128 Htable[16], u64 H[2])
{
    u128 V;
# if defined(OPENSSL_SMALL_FOOTPRINT)
    int i;
# endif

    Htable[0].hi = 0;
    Htable[0].lo = 0;
    V.hi = H[0];
    V.lo = H[1];

# if defined(OPENSSL_SMALL_FOOTPRINT)
    for (Htable[8] = V, i = 4; i > 0; i >>= 1) {
        REDUCE1BIT(V);
        Htable[i] = V;
    }

    for (i = 2; i < 16; i <<= 1) {
        u128 *Hi = Htable + i;
        int j;
        for (V = *Hi, j = 1; j < i; ++j) {
            Hi[j].hi = V.hi ^ Htable[j].hi;
            Hi[j].lo = V.lo ^ Htable[j].lo;
        }
    }
# else
    Htable[8] = V;
    REDUCE1BIT(V);
    Htable[4] = V;
    REDUCE1BIT(V);
    Htable[2] = V;
    REDUCE1BIT(V);
    Htable[1] = V;
    Htable[3].hi = V.hi ^ Htable[2].hi, Htable[3].lo = V.lo ^ Htable[2].lo;
    V = Htable[4];
    Htable[5].hi = V.hi ^ Htable[1].hi, Htable[5].lo = V.lo ^ Htable[1].lo;
    Htable[6].hi = V.hi ^ Htable[2].hi, Htable[6].lo = V.lo ^ Htable[2].lo;
    Htable[7].hi = V.hi ^ Htable[3].hi, Htable[7].lo = V.lo ^ Htable[3].lo;
    V = Htable[8];
    Htable[9].hi = V.hi ^ Htable[1].hi, Htable[9].lo = V.lo ^ Htable[1].lo;
    Htable[10].hi = V.hi ^ Htable[2].hi, Htable[10].lo = V.lo ^ Htable[2].lo;
    Htable[11].hi = V.hi ^ Htable[3].hi, Htable[11].lo = V.lo ^ Htable[3].lo;
    Htable[12].hi = V.hi ^ Htable[4].hi, Htable[12].lo = V.lo ^ Htable[4].lo;
    Htable[13].hi = V.hi ^ Htable[5].hi, Htable[13].lo = V.lo ^ Htable[5].lo;
    Htable[14].hi = V.hi ^ Htable[6].hi, Htable[14].lo = V.lo ^ Htable[6].lo;
    Htable[15].hi = V.hi ^ Htable[7].hi, Htable[15].lo = V.lo ^ Htable[7].lo;
# endif
# if defined(GHASH_ASM) && (defined(__arm__) || defined(__arm))
    /*
     * ARM assembler expects specific dword order in Htable.
     */
    {
        int j;
        const union {
            long one;
            char little;
        } is_endian = { 1 };

        if (is_endian.little)
            for (j = 0; j < 16; ++j) {
                V = Htable[j];
                Htable[j].hi = V.lo;
                Htable[j].lo = V.hi;
        } else
            for (j = 0; j < 16; ++j) {
                V = Htable[j];
                Htable[j].hi = V.lo << 32 | V.lo >> 32;
                Htable[j].lo = V.hi << 32 | V.hi >> 32;
            }
    }
# endif
}