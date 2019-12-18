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
typedef  void* uint8_t ;
typedef  int uint64_t ;
typedef  int uint32_t ;

/* Variables and functions */
 int PTR_TO_UINT (void**) ; 

void * MemSet64(void* pDst, uint8_t val, uint32_t size)
{
    uint64_t val64;
    uint64_t *pDst64;
    uint8_t  *p_Dst8;

    p_Dst8 = (uint8_t*)(pDst);

    /* generate four 8-bit val's in 32-bit container */
    val64  = (uint64_t) val;
    val64 |= (val64 <<  8);
    val64 |= (val64 << 16);
    val64 |= (val64 << 24);
    val64 |= (val64 << 32);

    /* align destination to 64 */
    while((PTR_TO_UINT(p_Dst8) & 7) && size) /* (pDst mod 8) > 0 and size > 0 */
    {
        *p_Dst8++ = val;
        size--;
    }

    /* 64-bit chunks */
    pDst64 = (uint64_t*)(p_Dst8);
    while (size >> 4) /* size >= 8 */
    {
        *pDst64++ = val64;
        size -= 8;
    }

    /* complete the leftovers */
    p_Dst8 = (uint8_t*)(pDst64);
    while (size--)
        *p_Dst8++ = val;

    return pDst;
}