#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {size_t* outBufsDataSizes; size_t outBuf_Rem; size_t outBuf; scalar_t__ outStream; int /*<<< orphan*/ ** outBufs; } ;
typedef  int /*<<< orphan*/  SRes ;
typedef  TYPE_1__ CLzma2Enc ;
typedef  int /*<<< orphan*/  Byte ;

/* Variables and functions */
 size_t ISeqOutStream_Write (scalar_t__,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  SZ_ERROR_OUTPUT_EOF ; 
 int /*<<< orphan*/  SZ_ERROR_WRITE ; 
 int /*<<< orphan*/  SZ_OK ; 
 int /*<<< orphan*/  memcpy (size_t,int /*<<< orphan*/  const*,size_t) ; 

__attribute__((used)) static SRes Lzma2Enc_MtCallback_Write(void *pp, unsigned outBufIndex)
{
  CLzma2Enc *me = (CLzma2Enc *)pp;
  size_t size = me->outBufsDataSizes[outBufIndex];
  const Byte *data = me->outBufs[outBufIndex];
  
  if (me->outStream)
    return ISeqOutStream_Write(me->outStream, data, size) == size ? SZ_OK : SZ_ERROR_WRITE;
  
  if (size > me->outBuf_Rem)
    return SZ_ERROR_OUTPUT_EOF;
  memcpy(me->outBuf, data, size);
  me->outBuf_Rem -= size;
  me->outBuf += size;
  return SZ_OK;
}