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
typedef  scalar_t__ UInt64 ;
struct TYPE_3__ {int prop; int finishMode; scalar_t__ inLim; scalar_t__ inPos; scalar_t__ inProcessed; scalar_t__ outProcessed; scalar_t__ outSize; int /*<<< orphan*/  outSize_Defined; int /*<<< orphan*/ * inStream; int /*<<< orphan*/  props; } ;
typedef  int /*<<< orphan*/  SRes ;
typedef  int /*<<< orphan*/  ISeqInStream ;
typedef  int /*<<< orphan*/  CLzma2DecMtProps ;
typedef  scalar_t__ CLzma2DecMtHandle ;
typedef  TYPE_1__ CLzma2DecMt ;
typedef  int Byte ;

/* Variables and functions */
 int /*<<< orphan*/  False ; 
 int /*<<< orphan*/  Lzma2Dec_Prepare_ST (TYPE_1__*) ; 
 int /*<<< orphan*/  SZ_ERROR_UNSUPPORTED ; 
 int /*<<< orphan*/  True ; 

SRes Lzma2DecMt_Init(CLzma2DecMtHandle pp,
    Byte prop,
    const CLzma2DecMtProps *props,
    const UInt64 *outDataSize, int finishMode,
    ISeqInStream *inStream)
{
  CLzma2DecMt *p = (CLzma2DecMt *)pp;

  if (prop > 40)
    return SZ_ERROR_UNSUPPORTED;

  p->prop = prop;
  p->props = *props;

  p->inStream = inStream;

  p->outSize = 0;
  p->outSize_Defined = False;
  if (outDataSize)
  {
    p->outSize_Defined = True;
    p->outSize = *outDataSize;
  }
  p->finishMode = finishMode;

  p->outProcessed = 0;
  p->inProcessed = 0;

  p->inPos = 0;
  p->inLim = 0;

  return Lzma2Dec_Prepare_ST(p);
}