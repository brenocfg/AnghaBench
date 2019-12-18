#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UInt64 ;
typedef  scalar_t__ UInt32 ;
struct TYPE_11__ {TYPE_1__* outStream; } ;
struct TYPE_10__ {scalar_t__ nowPos64; TYPE_4__ rc; int /*<<< orphan*/  result; void* finished; void* writeEndMark; } ;
struct TYPE_8__ {int /*<<< orphan*/  Write; } ;
struct TYPE_9__ {size_t rem; void* overflow; TYPE_1__ vt; int /*<<< orphan*/ * data; } ;
typedef  int /*<<< orphan*/  SRes ;
typedef  TYPE_2__ CLzmaEnc_SeqOutStreamBuf ;
typedef  scalar_t__ CLzmaEncHandle ;
typedef  TYPE_3__ CLzmaEnc ;
typedef  int /*<<< orphan*/  Byte ;
typedef  scalar_t__ BoolInt ;

/* Variables and functions */
 void* False ; 
 int /*<<< orphan*/  LzmaEnc_CodeOneBlock (TYPE_3__*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  LzmaEnc_Init (TYPE_3__*) ; 
 int /*<<< orphan*/  LzmaEnc_InitPrices (TYPE_3__*) ; 
 int /*<<< orphan*/  RangeEnc_Init (TYPE_4__*) ; 
 int /*<<< orphan*/  SZ_ERROR_OUTPUT_EOF ; 
 int /*<<< orphan*/  SZ_OK ; 
 int /*<<< orphan*/  SeqOutStreamBuf_Write ; 

SRes LzmaEnc_CodeOneMemBlock(CLzmaEncHandle pp, BoolInt reInit,
    Byte *dest, size_t *destLen, UInt32 desiredPackSize, UInt32 *unpackSize)
{
  CLzmaEnc *p = (CLzmaEnc *)pp;
  UInt64 nowPos64;
  SRes res;
  CLzmaEnc_SeqOutStreamBuf outStream;

  outStream.vt.Write = SeqOutStreamBuf_Write;
  outStream.data = dest;
  outStream.rem = *destLen;
  outStream.overflow = False;

  p->writeEndMark = False;
  p->finished = False;
  p->result = SZ_OK;

  if (reInit)
    LzmaEnc_Init(p);
  LzmaEnc_InitPrices(p);

  nowPos64 = p->nowPos64;
  RangeEnc_Init(&p->rc);
  p->rc.outStream = &outStream.vt;

  if (desiredPackSize == 0)
    return SZ_ERROR_OUTPUT_EOF;

  res = LzmaEnc_CodeOneBlock(p, desiredPackSize, *unpackSize);
  
  *unpackSize = (UInt32)(p->nowPos64 - nowPos64);
  *destLen -= outStream.rem;
  if (outStream.overflow)
    return SZ_ERROR_OUTPUT_EOF;

  return res;
}