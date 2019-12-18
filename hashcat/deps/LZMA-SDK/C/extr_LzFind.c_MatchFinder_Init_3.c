#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ streamEndWasReached; int /*<<< orphan*/  result; int /*<<< orphan*/  cyclicBufferSize; int /*<<< orphan*/  streamPos; int /*<<< orphan*/  pos; int /*<<< orphan*/  bufferBase; int /*<<< orphan*/  buffer; scalar_t__ cyclicBufferPos; } ;
typedef  TYPE_1__ CMatchFinder ;

/* Variables and functions */
 int /*<<< orphan*/  MatchFinder_ReadBlock (TYPE_1__*) ; 
 int /*<<< orphan*/  MatchFinder_SetLimits (TYPE_1__*) ; 
 int /*<<< orphan*/  SZ_OK ; 

void MatchFinder_Init_3(CMatchFinder *p, int readData)
{
  p->cyclicBufferPos = 0;
  p->buffer = p->bufferBase;
  p->pos =
  p->streamPos = p->cyclicBufferSize;
  p->result = SZ_OK;
  p->streamEndWasReached = 0;
  
  if (readData)
    MatchFinder_ReadBlock(p);
  
  MatchFinder_SetLimits(p);
}