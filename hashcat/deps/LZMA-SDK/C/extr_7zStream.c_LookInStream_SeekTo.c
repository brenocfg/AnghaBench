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
typedef  int /*<<< orphan*/  Int64 ;
typedef  int /*<<< orphan*/  ILookInStream ;

/* Variables and functions */
 int /*<<< orphan*/  ILookInStream_Seek (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SZ_SEEK_SET ; 

SRes LookInStream_SeekTo(const ILookInStream *stream, UInt64 offset)
{
  Int64 t = offset;
  return ILookInStream_Seek(stream, &t, SZ_SEEK_SET);
}