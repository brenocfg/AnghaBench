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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
typedef  scalar_t__ p_Src32 ;

/* Variables and functions */
 int GET_UINT32 (int) ; 
 int /*<<< orphan*/  GET_UINT8 (int /*<<< orphan*/ ) ; 
 int PTR_TO_UINT (int /*<<< orphan*/ *) ; 

void * IO2MemCpy32(void* pDst,void* pSrc, uint32_t size)
{
    uint32_t leftAlign;
    uint32_t rightAlign;
    uint32_t lastWord;
    uint32_t currWord;
    uint32_t *p_Src32;
    uint32_t *p_Dst32;
    uint8_t  *p_Src8;
    uint8_t  *p_Dst8;

    p_Src8 = (uint8_t*)(pSrc);
    p_Dst8 = (uint8_t*)(pDst);
    /* first copy byte by byte till the source first alignment
     * this step is necessary to ensure we do not even try to access
     * data which is before the source buffer, hence it is not ours.
     */
    while((PTR_TO_UINT(p_Src8) & 3) && size) /* (pSrc mod 4) > 0 and size > 0 */
    {
        *p_Dst8 = GET_UINT8(*p_Src8);
        p_Dst8++;p_Src8++;
        size--;
    }

    /* align destination (possibly disaligning source)*/
    while((PTR_TO_UINT(p_Dst8) & 3) && size) /* (pDst mod 4) > 0 and size > 0 */
    {
        *p_Dst8 = GET_UINT8(*p_Src8);
        p_Dst8++;p_Src8++;
        size--;
    }

    /* dest is aligned and source is not necessarily aligned */
    leftAlign = (uint32_t)((PTR_TO_UINT(p_Src8) & 3) << 3); /* leftAlign = (pSrc mod 4)*8 */
    rightAlign = 32 - leftAlign;

    if (leftAlign == 0)
    {
        /* source is also aligned */
        p_Src32 = (uint32_t*)(p_Src8);
        p_Dst32 = (uint32_t*)(p_Dst8);
        while (size >> 2) /* size >= 4 */
        {
            *p_Dst32 = GET_UINT32(*p_Src32);
            p_Dst32++;p_Src32++;
            size -= 4;
        }
        p_Src8 = (uint8_t*)(p_Src32);
        p_Dst8 = (uint8_t*)(p_Dst32);
    }
    else
    {
        /* source is not aligned (destination is aligned)*/
        p_Src32 = (uint32_t*)(p_Src8 - (leftAlign >> 3));
        p_Dst32 = (uint32_t*)(p_Dst8);
        lastWord = GET_UINT32(*p_Src32);
        p_Src32++;
        while(size >> 3) /* size >= 8 */
        {
            currWord = GET_UINT32(*p_Src32);
            *p_Dst32 = (lastWord << leftAlign) | (currWord >> rightAlign);
            lastWord = currWord;
            p_Src32++;p_Dst32++;
            size -= 4;
        }
        p_Dst8 = (uint8_t*)(p_Dst32);
        p_Src8 = (uint8_t*)(p_Src32) - 4 + (leftAlign >> 3);
    }

    /* complete the left overs */
    while (size--)
    {
        *p_Dst8 = GET_UINT8(*p_Src8);
        p_Dst8++;p_Src8++;
    }

    return pDst;
}