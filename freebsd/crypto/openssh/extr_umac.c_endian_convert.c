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
typedef  int UWORD ;
typedef  int UINT32 ;

/* Variables and functions */
 int LOAD_UINT32_REVERSED (int*) ; 

__attribute__((used)) static void endian_convert(void *buf, UWORD bpw, UINT32 num_bytes)
/* We endian convert the keys on little-endian computers to               */
/* compensate for the lack of big-endian memory reads during hashing.     */
{
    UWORD iters = num_bytes / bpw;
    if (bpw == 4) {
        UINT32 *p = (UINT32 *)buf;
        do {
            *p = LOAD_UINT32_REVERSED(p);
            p++;
        } while (--iters);
    } else if (bpw == 8) {
        UINT32 *p = (UINT32 *)buf;
        UINT32 t;
        do {
            t = LOAD_UINT32_REVERSED(p+1);
            p[1] = LOAD_UINT32_REVERSED(p);
            p[0] = t;
            p += 2;
        } while (--iters);
    }
}