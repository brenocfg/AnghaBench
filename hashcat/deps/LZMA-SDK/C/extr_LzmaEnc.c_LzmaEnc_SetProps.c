#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int UInt64 ;
struct TYPE_6__ {unsigned int numHashBytes; int /*<<< orphan*/  cutValue; scalar_t__ btMode; } ;
struct TYPE_8__ {int dictSize; unsigned int numFastBytes; scalar_t__ lc; scalar_t__ lp; scalar_t__ pb; int fastMode; int multiThread; int /*<<< orphan*/  writeEndMark; TYPE_1__ matchFinderBase; } ;
struct TYPE_7__ {scalar_t__ lc; scalar_t__ lp; scalar_t__ pb; int dictSize; unsigned int fb; scalar_t__ algo; int numHashBytes; int numThreads; int /*<<< orphan*/  writeEndMark; int /*<<< orphan*/  mc; scalar_t__ btMode; } ;
typedef  int /*<<< orphan*/  SRes ;
typedef  TYPE_2__ CLzmaEncProps ;
typedef  scalar_t__ CLzmaEncHandle ;
typedef  TYPE_3__ CLzmaEnc ;
typedef  scalar_t__ Byte ;

/* Variables and functions */
 scalar_t__ LZMA_LC_MAX ; 
 scalar_t__ LZMA_LP_MAX ; 
 unsigned int LZMA_MATCH_LEN_MAX ; 
 scalar_t__ LZMA_PB_MAX ; 
 int /*<<< orphan*/  LzmaEncProps_Normalize (TYPE_2__*) ; 
 int /*<<< orphan*/  SZ_ERROR_PARAM ; 
 int /*<<< orphan*/  SZ_OK ; 
 int kDicLogSizeMaxCompress ; 
 int kLzmaMaxHistorySize ; 

SRes LzmaEnc_SetProps(CLzmaEncHandle pp, const CLzmaEncProps *props2)
{
  CLzmaEnc *p = (CLzmaEnc *)pp;
  CLzmaEncProps props = *props2;
  LzmaEncProps_Normalize(&props);

  if (props.lc > LZMA_LC_MAX
      || props.lp > LZMA_LP_MAX
      || props.pb > LZMA_PB_MAX
      || props.dictSize > ((UInt64)1 << kDicLogSizeMaxCompress)
      || props.dictSize > kLzmaMaxHistorySize)
    return SZ_ERROR_PARAM;

  p->dictSize = props.dictSize;
  {
    unsigned fb = props.fb;
    if (fb < 5)
      fb = 5;
    if (fb > LZMA_MATCH_LEN_MAX)
      fb = LZMA_MATCH_LEN_MAX;
    p->numFastBytes = fb;
  }
  p->lc = props.lc;
  p->lp = props.lp;
  p->pb = props.pb;
  p->fastMode = (props.algo == 0);
  // p->_maxMode = True;
  p->matchFinderBase.btMode = (Byte)(props.btMode ? 1 : 0);
  {
    unsigned numHashBytes = 4;
    if (props.btMode)
    {
      if (props.numHashBytes < 2)
        numHashBytes = 2;
      else if (props.numHashBytes < 4)
        numHashBytes = props.numHashBytes;
    }
    p->matchFinderBase.numHashBytes = numHashBytes;
  }

  p->matchFinderBase.cutValue = props.mc;

  p->writeEndMark = props.writeEndMark;

  #ifndef _7ZIP_ST
  /*
  if (newMultiThread != _multiThread)
  {
    ReleaseMatchFinder();
    _multiThread = newMultiThread;
  }
  */
  p->multiThread = (props.numThreads > 1);
  #endif

  return SZ_OK;
}