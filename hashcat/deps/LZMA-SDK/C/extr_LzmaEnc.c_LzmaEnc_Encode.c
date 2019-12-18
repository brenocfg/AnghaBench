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
typedef  int /*<<< orphan*/  SRes ;
typedef  int /*<<< orphan*/  ISzAllocPtr ;
typedef  int /*<<< orphan*/  ISeqOutStream ;
typedef  int /*<<< orphan*/  ISeqInStream ;
typedef  int /*<<< orphan*/  ICompressProgress ;
typedef  scalar_t__ CLzmaEncHandle ;
typedef  int /*<<< orphan*/  CLzmaEnc ;

/* Variables and functions */
 int /*<<< orphan*/  LzmaEnc_Encode2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LzmaEnc_Prepare (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RINOK (int /*<<< orphan*/ ) ; 

SRes LzmaEnc_Encode(CLzmaEncHandle pp, ISeqOutStream *outStream, ISeqInStream *inStream, ICompressProgress *progress,
    ISzAllocPtr alloc, ISzAllocPtr allocBig)
{
  RINOK(LzmaEnc_Prepare(pp, outStream, inStream, alloc, allocBig));
  return LzmaEnc_Encode2((CLzmaEnc *)pp, progress);
}