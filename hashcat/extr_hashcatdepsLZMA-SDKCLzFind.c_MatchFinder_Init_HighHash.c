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
struct TYPE_3__ {int fixedHashSize; scalar_t__ hashMask; int /*<<< orphan*/ * hash; } ;
typedef  TYPE_1__ CMatchFinder ;
typedef  int /*<<< orphan*/  CLzRef ;

/* Variables and functions */
 int /*<<< orphan*/  kEmptyHashValue ; 

void MatchFinder_Init_HighHash(CMatchFinder *p)
{
  size_t i;
  CLzRef *items = p->hash + p->fixedHashSize;
  size_t numItems = (size_t)p->hashMask + 1;
  for (i = 0; i < numItems; i++)
    items[i] = kEmptyHashValue;
}