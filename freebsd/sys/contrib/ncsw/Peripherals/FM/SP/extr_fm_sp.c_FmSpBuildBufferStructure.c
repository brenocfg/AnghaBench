#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint32_t ;
typedef  int uint16_t ;
struct TYPE_11__ {int extBufOffset; int privDataSize; int prsResultOffset; int timeStampOffset; int hashResultOffset; int pcdInfoOffset; int size; int intContextOffset; int startMargins; int manipExtraSpace; int manipOffset; int dataAlign; int dataOffset; scalar_t__ passPrsResult; scalar_t__ passHashResult; scalar_t__ passTimeStamp; scalar_t__ passAllOtherPCDInfo; } ;
typedef  TYPE_1__ t_FmSpIntContextDataCopy ;
typedef  TYPE_1__ t_FmSpBufferOffsets ;
typedef  TYPE_1__ t_FmSpBufMargins ;
typedef  int /*<<< orphan*/  t_FmPrsResult ;
typedef  TYPE_1__ t_FmBufferPrefixContent ;
typedef  int /*<<< orphan*/  t_Error ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_COND (TYPE_1__*) ; 
 int CAPWAP_FRAG_EXTRA_SPACE ; 
 int /*<<< orphan*/  E_INVALID_VALUE ; 
 int /*<<< orphan*/  E_OK ; 
 scalar_t__ ILLEGAL_BASE ; 
 int /*<<< orphan*/  MAJOR ; 
 int OFFSET_UNITS ; 
 int /*<<< orphan*/  RETURN_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SANITY_CHECK_RETURN_ERROR (TYPE_1__*,int /*<<< orphan*/ ) ; 

t_Error FmSpBuildBufferStructure(t_FmSpIntContextDataCopy   *p_FmSpIntContextDataCopy,
                                 t_FmBufferPrefixContent     *p_BufferPrefixContent,
                                 t_FmSpBufMargins            *p_FmSpBufMargins,
                                 t_FmSpBufferOffsets         *p_FmSpBufferOffsets,
                                 uint8_t                     *internalBufferOffset)
{
    uint32_t                        tmp;

    SANITY_CHECK_RETURN_ERROR(p_FmSpIntContextDataCopy,  E_INVALID_VALUE);
    ASSERT_COND(p_FmSpIntContextDataCopy);
    ASSERT_COND(p_BufferPrefixContent);
    ASSERT_COND(p_FmSpBufMargins);
    ASSERT_COND(p_FmSpBufferOffsets);

    /* Align start of internal context data to 16 byte */
    p_FmSpIntContextDataCopy->extBufOffset =
        (uint16_t)((p_BufferPrefixContent->privDataSize & (OFFSET_UNITS-1)) ?
            ((p_BufferPrefixContent->privDataSize + OFFSET_UNITS) & ~(uint16_t)(OFFSET_UNITS-1)) :
             p_BufferPrefixContent->privDataSize);

    /* Translate margin and intContext params to FM parameters */
    /* Initialize with illegal value. Later we'll set legal values. */
    p_FmSpBufferOffsets->prsResultOffset = (uint32_t)ILLEGAL_BASE;
    p_FmSpBufferOffsets->timeStampOffset = (uint32_t)ILLEGAL_BASE;
    p_FmSpBufferOffsets->hashResultOffset= (uint32_t)ILLEGAL_BASE;
    p_FmSpBufferOffsets->pcdInfoOffset   = (uint32_t)ILLEGAL_BASE;

    /* Internally the driver supports 4 options
       1. prsResult/timestamp/hashResult selection (in fact 8 options, but for simplicity we'll
          relate to it as 1).
       2. All IC context (from AD) not including debug.*/

    /* This 'if' covers option 2. We copy from beginning of context. */
    if (p_BufferPrefixContent->passAllOtherPCDInfo)
    {
        p_FmSpIntContextDataCopy->size = 128; /* must be aligned to 16 */
        /* Start copying data after 16 bytes (FD) from the beginning of the internal context */
        p_FmSpIntContextDataCopy->intContextOffset = 16;

        if (p_BufferPrefixContent->passAllOtherPCDInfo)
            p_FmSpBufferOffsets->pcdInfoOffset = p_FmSpIntContextDataCopy->extBufOffset;
        if (p_BufferPrefixContent->passPrsResult)
            p_FmSpBufferOffsets->prsResultOffset =
                (uint32_t)(p_FmSpIntContextDataCopy->extBufOffset + 16);
        if (p_BufferPrefixContent->passTimeStamp)
            p_FmSpBufferOffsets->timeStampOffset =
                (uint32_t)(p_FmSpIntContextDataCopy->extBufOffset + 48);
        if (p_BufferPrefixContent->passHashResult)
            p_FmSpBufferOffsets->hashResultOffset =
                (uint32_t)(p_FmSpIntContextDataCopy->extBufOffset + 56);
    }
    else
    {
        /* This case covers the options under 1 */
        /* Copy size must be in 16-byte granularity. */
        p_FmSpIntContextDataCopy->size =
            (uint16_t)((p_BufferPrefixContent->passPrsResult ? 32 : 0) +
                      ((p_BufferPrefixContent->passTimeStamp ||
                      p_BufferPrefixContent->passHashResult) ? 16 : 0));

        /* Align start of internal context data to 16 byte */
        p_FmSpIntContextDataCopy->intContextOffset =
            (uint8_t)(p_BufferPrefixContent->passPrsResult ? 32 :
                      ((p_BufferPrefixContent->passTimeStamp  ||
                       p_BufferPrefixContent->passHashResult) ? 64 : 0));

        if (p_BufferPrefixContent->passPrsResult)
            p_FmSpBufferOffsets->prsResultOffset = p_FmSpIntContextDataCopy->extBufOffset;
        if (p_BufferPrefixContent->passTimeStamp)
            p_FmSpBufferOffsets->timeStampOffset =  p_BufferPrefixContent->passPrsResult ?
                                        (p_FmSpIntContextDataCopy->extBufOffset + sizeof(t_FmPrsResult)) :
                                        p_FmSpIntContextDataCopy->extBufOffset;
        if (p_BufferPrefixContent->passHashResult)
            /* If PR is not requested, whether TS is requested or not, IC will be copied from TS */
            p_FmSpBufferOffsets->hashResultOffset = p_BufferPrefixContent->passPrsResult ?
                                          (p_FmSpIntContextDataCopy->extBufOffset + sizeof(t_FmPrsResult) + 8) :
                                          p_FmSpIntContextDataCopy->extBufOffset + 8;
    }

    if (p_FmSpIntContextDataCopy->size)
        p_FmSpBufMargins->startMargins =
            (uint16_t)(p_FmSpIntContextDataCopy->extBufOffset +
                       p_FmSpIntContextDataCopy->size);
    else
        /* No Internal Context passing, STartMargin is immediately after privateInfo */
        p_FmSpBufMargins->startMargins = p_BufferPrefixContent->privDataSize;

    /* save extra space for manip in both external and internal buffers */
    if (p_BufferPrefixContent->manipExtraSpace)
    {
        uint8_t extraSpace;
#ifdef FM_CAPWAP_SUPPORT
        if ((p_BufferPrefixContent->manipExtraSpace + CAPWAP_FRAG_EXTRA_SPACE) >= 256)
            RETURN_ERROR(MAJOR, E_INVALID_VALUE,
                         ("p_BufferPrefixContent->manipExtraSpace should be less than %d",
                          256-CAPWAP_FRAG_EXTRA_SPACE));
        extraSpace = (uint8_t)(p_BufferPrefixContent->manipExtraSpace + CAPWAP_FRAG_EXTRA_SPACE);
#else
        extraSpace = p_BufferPrefixContent->manipExtraSpace;
#endif /* FM_CAPWAP_SUPPORT */
        p_FmSpBufferOffsets->manipOffset = p_FmSpBufMargins->startMargins;
        p_FmSpBufMargins->startMargins += extraSpace;
        *internalBufferOffset = extraSpace;
    }

    /* align data start */
    tmp = (uint32_t)(p_FmSpBufMargins->startMargins % p_BufferPrefixContent->dataAlign);
    if (tmp)
        p_FmSpBufMargins->startMargins += (p_BufferPrefixContent->dataAlign-tmp);
    p_FmSpBufferOffsets->dataOffset = p_FmSpBufMargins->startMargins;

    return E_OK;
}