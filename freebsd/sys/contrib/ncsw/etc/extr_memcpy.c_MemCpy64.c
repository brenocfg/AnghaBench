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
typedef  int uint64_t ;
typedef  int uint32_t ;
typedef  scalar_t__ pSrc64 ;

/* Variables and functions */
 int PTR_TO_UINT (int /*<<< orphan*/ *) ; 

void * MemCpy64(void* pDst,void* pSrc, uint32_t size)
{
    uint32_t leftAlign;
    uint32_t rightAlign;
    uint64_t lastWord;
    uint64_t currWord;
    uint64_t *pSrc64;
    uint64_t *pDst64;
    uint8_t  *p_Src8;
    uint8_t  *p_Dst8;

    p_Src8 = (uint8_t*)(pSrc);
    p_Dst8 = (uint8_t*)(pDst);
    /* first copy byte by byte till the source first alignment
     * this step is necessarily to ensure we do not even try to access
     * data which is before the source buffer, hence it is not ours.
     */
    while((PTR_TO_UINT(p_Src8) & 7) && size) /* (pSrc mod 8) > 0 and size > 0 */
    {
        *p_Dst8++ = *p_Src8++;
        size--;
    }

    /* align destination (possibly disaligning source)*/
    while((PTR_TO_UINT(p_Dst8) & 7) && size) /* (pDst mod 8) > 0 and size > 0 */
    {
        *p_Dst8++ = *p_Src8++;
        size--;
    }

    /* dest is aligned and source is not necessarily aligned */
    leftAlign = (uint32_t)((PTR_TO_UINT(p_Src8) & 7) << 3); /* leftAlign = (pSrc mod 8)*8 */
    rightAlign = 64 - leftAlign;


    if (leftAlign == 0)
    {
        /* source is also aligned */
        pSrc64 = (uint64_t*)(p_Src8);
        pDst64 = (uint64_t*)(p_Dst8);
        while (size >> 3) /* size >= 8 */
        {
            *pDst64++ = *pSrc64++;
            size -= 8;
        }
        p_Src8 = (uint8_t*)(pSrc64);
        p_Dst8 = (uint8_t*)(pDst64);
    }
    else
    {
        /* source is not aligned (destination is aligned)*/
        pSrc64 = (uint64_t*)(p_Src8 - (leftAlign >> 3));
        pDst64 = (uint64_t*)(p_Dst8);
        lastWord = *pSrc64++;
        while(size >> 4) /* size >= 16 */
        {
            currWord = *pSrc64;
            *pDst64 = (lastWord << leftAlign) | (currWord >> rightAlign);
            lastWord = currWord;
            pSrc64++;
            pDst64++;
            size -= 8;
        }
        p_Dst8 = (uint8_t*)(pDst64);
        p_Src8 = (uint8_t*)(pSrc64) - 8 + (leftAlign >> 3);
    }

    /* complete the left overs */
    while (size--)
        *p_Dst8++ = *p_Src8++;

    return pDst;
}