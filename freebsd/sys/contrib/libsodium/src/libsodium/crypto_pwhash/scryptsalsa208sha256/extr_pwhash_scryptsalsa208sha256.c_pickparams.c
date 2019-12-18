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
typedef  int uint64_t ;
typedef  int uint32_t ;

/* Variables and functions */

__attribute__((used)) static int
pickparams(unsigned long long opslimit, const size_t memlimit,
           uint32_t *const N_log2, uint32_t *const p, uint32_t *const r)
{
    unsigned long long maxN;
    unsigned long long maxrp;

    if (opslimit < 32768) {
        opslimit = 32768;
    }
    *r = 8;
    if (opslimit < memlimit / 32) {
        *p = 1;
        maxN = opslimit / (*r * 4);
        for (*N_log2 = 1; *N_log2 < 63; *N_log2 += 1) {
            if ((uint64_t)(1) << *N_log2 > maxN / 2) {
                break;
            }
        }
    } else {
        maxN = memlimit / ((size_t) *r * 128);
        for (*N_log2 = 1; *N_log2 < 63; *N_log2 += 1) {
            if ((uint64_t)(1) << *N_log2 > maxN / 2) {
                break;
            }
        }
        maxrp = (opslimit / 4) / ((uint64_t)(1) << *N_log2);
        /* LCOV_EXCL_START */
        if (maxrp > 0x3fffffff) {
            maxrp = 0x3fffffff;
        }
        /* LCOV_EXCL_STOP */
        *p = (uint32_t)(maxrp) / *r;
    }
    return 0;
}