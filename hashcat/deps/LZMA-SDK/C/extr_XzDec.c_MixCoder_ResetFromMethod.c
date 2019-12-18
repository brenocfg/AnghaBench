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
typedef  int UInt64 ;
struct TYPE_3__ {int /*<<< orphan*/ * coders; } ;
typedef  int /*<<< orphan*/  SRes ;
typedef  int /*<<< orphan*/  IStateCoder ;
typedef  TYPE_1__ CMixCoder ;
typedef  int /*<<< orphan*/  Byte ;

/* Variables and functions */
 int /*<<< orphan*/  Lzma2State_ResetOutBuf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  SZ_ERROR_UNSUPPORTED ; 
#define  XZ_ID_LZMA2 128 

__attribute__((used)) static SRes MixCoder_ResetFromMethod(CMixCoder *p, unsigned coderIndex, UInt64 methodId, Byte *outBuf, size_t outBufSize)
{
  IStateCoder *sc = &p->coders[coderIndex];
  switch (methodId)
  {
    case XZ_ID_LZMA2: return Lzma2State_ResetOutBuf(sc, outBuf, outBufSize);
  }
  return SZ_ERROR_UNSUPPORTED;
}