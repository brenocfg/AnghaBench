#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UInt64 ;
typedef  int UInt32 ;
struct TYPE_4__ {int* crc; scalar_t__ expectedDataSize; int /*<<< orphan*/ * hash; scalar_t__ directInput; int /*<<< orphan*/ * bufferBase; } ;
typedef  scalar_t__ Int64 ;
typedef  TYPE_1__ CMatchFinder ;

/* Variables and functions */
 int /*<<< orphan*/  MatchFinder_SetDefaultSettings (TYPE_1__*) ; 
 int kCrcPoly ; 

void MatchFinder_Construct(CMatchFinder *p)
{
  unsigned i;
  p->bufferBase = NULL;
  p->directInput = 0;
  p->hash = NULL;
  p->expectedDataSize = (UInt64)(Int64)-1;
  MatchFinder_SetDefaultSettings(p);

  for (i = 0; i < 256; i++)
  {
    UInt32 r = (UInt32)i;
    unsigned j;
    for (j = 0; j < 8; j++)
      r = (r >> 1) ^ (kCrcPoly & ((UInt32)0 - (r & 1)));
    p->crc[i] = r;
  }
}