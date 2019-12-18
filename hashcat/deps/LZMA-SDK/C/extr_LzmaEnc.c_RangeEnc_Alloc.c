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
struct TYPE_3__ {int /*<<< orphan*/ * bufBase; int /*<<< orphan*/ * bufLim; } ;
typedef  int /*<<< orphan*/  ISzAllocPtr ;
typedef  TYPE_1__ CRangeEnc ;
typedef  int /*<<< orphan*/  Byte ;

/* Variables and functions */
 scalar_t__ ISzAlloc_Alloc (int /*<<< orphan*/ ,int) ; 
 int RC_BUF_SIZE ; 

__attribute__((used)) static int RangeEnc_Alloc(CRangeEnc *p, ISzAllocPtr alloc)
{
  if (!p->bufBase)
  {
    p->bufBase = (Byte *)ISzAlloc_Alloc(alloc, RC_BUF_SIZE);
    if (!p->bufBase)
      return 0;
    p->bufLim = p->bufBase + RC_BUF_SIZE;
  }
  return 1;
}