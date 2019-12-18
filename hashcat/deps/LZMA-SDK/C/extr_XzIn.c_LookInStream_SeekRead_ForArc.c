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
typedef  int /*<<< orphan*/  UInt64 ;
typedef  int /*<<< orphan*/  SRes ;
typedef  int /*<<< orphan*/  ILookInStream ;

/* Variables and functions */
 int /*<<< orphan*/  LookInStream_Read (int /*<<< orphan*/ *,void*,size_t) ; 
 int /*<<< orphan*/  LookInStream_SeekTo (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RINOK (int /*<<< orphan*/ ) ; 

__attribute__((used)) static SRes LookInStream_SeekRead_ForArc(ILookInStream *stream, UInt64 offset, void *buf, size_t size)
{
  RINOK(LookInStream_SeekTo(stream, offset));
  return LookInStream_Read(stream, buf, size);
  /* return LookInStream_Read2(stream, buf, size, SZ_ERROR_NO_ARCHIVE); */
}