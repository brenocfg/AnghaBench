#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UInt64 ;
struct TYPE_8__ {scalar_t__ InSize; scalar_t__ DecodeRes; void* DataAfterEnd; void* NumBlocks_Defined; void* NumStreams_Defined; void* UnpackSize_Defined; int /*<<< orphan*/  NumBlocks; int /*<<< orphan*/  NumStreams; scalar_t__ DecodingTruncated; } ;
struct TYPE_7__ {int /*<<< orphan*/  numTotalBlocks; int /*<<< orphan*/  numStartedStreams; } ;
typedef  scalar_t__ SRes ;
typedef  scalar_t__ ECoderStatus ;
typedef  TYPE_1__ CXzUnpacker ;
typedef  TYPE_2__ CXzStatInfo ;
typedef  scalar_t__ Byte ;
typedef  scalar_t__ BoolInt ;

/* Variables and functions */
 scalar_t__ CODER_STATUS_NEEDS_MORE_INPUT ; 
 scalar_t__ SZ_ERROR_DATA ; 
 scalar_t__ SZ_ERROR_INPUT_EOF ; 
 scalar_t__ SZ_ERROR_NO_ARCHIVE ; 
 scalar_t__ SZ_OK ; 
 void* True ; 
 scalar_t__ XzUnpacker_GetExtraSize (TYPE_1__ const*) ; 
 int /*<<< orphan*/  XzUnpacker_IsStreamWasFinished (TYPE_1__ const*) ; 

__attribute__((used)) static SRes XzStatInfo_SetStat(const CXzUnpacker *dec,
    int finishMode,
    UInt64 readProcessed, UInt64 inProcessed,
    SRes res, ECoderStatus status,
    BoolInt decodingTruncated,
    CXzStatInfo *stat)
{
  UInt64 extraSize;
  
  stat->DecodingTruncated = (Byte)(decodingTruncated ? 1 : 0);
  stat->InSize = inProcessed;
  stat->NumStreams = dec->numStartedStreams;
  stat->NumBlocks = dec->numTotalBlocks;
  
  stat->UnpackSize_Defined = True;
  stat->NumStreams_Defined = True;
  stat->NumBlocks_Defined = True;
  
  extraSize = XzUnpacker_GetExtraSize(dec);
  
  if (res == SZ_OK)
  {
    if (status == CODER_STATUS_NEEDS_MORE_INPUT)
    {
      // CODER_STATUS_NEEDS_MORE_INPUT is expected status for correct xz streams
      extraSize = 0;
      if (!XzUnpacker_IsStreamWasFinished(dec))
        res = SZ_ERROR_INPUT_EOF;
    }
    else if (!decodingTruncated || finishMode) // (status == CODER_STATUS_NOT_FINISHED)
      res = SZ_ERROR_DATA;
  }
  else if (res == SZ_ERROR_NO_ARCHIVE)
  {
    /*
    SZ_ERROR_NO_ARCHIVE is possible for 2 states:
      XZ_STATE_STREAM_HEADER  - if bad signature or bad CRC
      XZ_STATE_STREAM_PADDING - if non-zero padding data
    extraSize / inProcessed don't include "bad" byte
    */
    if (inProcessed != extraSize) // if good streams before error
      if (extraSize != 0 || readProcessed != inProcessed)
      {
        stat->DataAfterEnd = True;
        // there is some good xz stream before. So we set SZ_OK
        res = SZ_OK;
      }
  }
  
  stat->DecodeRes = res;

  stat->InSize -= extraSize;
  return res;
}