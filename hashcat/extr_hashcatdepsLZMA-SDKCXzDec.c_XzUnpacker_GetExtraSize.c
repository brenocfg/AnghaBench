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
struct TYPE_3__ {scalar_t__ state; scalar_t__ pos; scalar_t__ padSize; } ;
typedef  TYPE_1__ CXzUnpacker ;

/* Variables and functions */
 scalar_t__ XZ_STATE_STREAM_HEADER ; 
 scalar_t__ XZ_STATE_STREAM_PADDING ; 

UInt64 XzUnpacker_GetExtraSize(const CXzUnpacker *p)
{
  UInt64 num = 0;
  if (p->state == XZ_STATE_STREAM_PADDING)
    num = p->padSize;
  else if (p->state == XZ_STATE_STREAM_HEADER)
    num = p->padSize + p->pos;
  return num;
}