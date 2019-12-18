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
typedef  int /*<<< orphan*/  SizeT ;
typedef  int /*<<< orphan*/  SRes ;
typedef  int /*<<< orphan*/  ECoderStatus ;
typedef  int /*<<< orphan*/  ECoderFinishMode ;
typedef  int /*<<< orphan*/  CXzUnpacker ;
typedef  int /*<<< orphan*/  Byte ;

/* Variables and functions */
 int /*<<< orphan*/  True ; 
 int /*<<< orphan*/  XzUnpacker_Code (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XzUnpacker_Init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XzUnpacker_SetOutBuf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

SRes XzUnpacker_CodeFull(CXzUnpacker *p, Byte *dest, SizeT *destLen,
    const Byte *src, SizeT *srcLen,
    ECoderFinishMode finishMode, ECoderStatus *status)
{
  XzUnpacker_Init(p);
  XzUnpacker_SetOutBuf(p, dest, *destLen);

  return XzUnpacker_Code(p,
      NULL, destLen,
      src, srcLen, True,
      finishMode, status);
}