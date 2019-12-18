#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t ptrdiff_t ;
typedef  scalar_t__ UInt32 ;
struct TYPE_4__ {scalar_t__ (* GetNumAvailableBytes ) (int /*<<< orphan*/ ) ;unsigned int (* GetMatches ) (int /*<<< orphan*/ ,int*) ;scalar_t__* (* GetPointerToCurrentPos ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_5__ {scalar_t__ numAvail; int* matches; unsigned int numFastBytes; int /*<<< orphan*/  matchFinderObj; TYPE_1__ matchFinder; int /*<<< orphan*/  additionalOffset; } ;
typedef  TYPE_2__ CLzmaEnc ;
typedef  scalar_t__ Byte ;

/* Variables and functions */
 scalar_t__ LZMA_MATCH_LEN_MAX ; 
 int g_STAT_OFFSET ; 
 int /*<<< orphan*/  printf (char*,int,unsigned int) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ) ; 
 unsigned int stub2 (int /*<<< orphan*/ ,int*) ; 
 scalar_t__* stub3 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned ReadMatchDistances(CLzmaEnc *p, unsigned *numPairsRes)
{
  unsigned numPairs;
  
  p->additionalOffset++;
  p->numAvail = p->matchFinder.GetNumAvailableBytes(p->matchFinderObj);
  numPairs = p->matchFinder.GetMatches(p->matchFinderObj, p->matches);
  *numPairsRes = numPairs;
  
  #ifdef SHOW_STAT
  printf("\n i = %u numPairs = %u    ", g_STAT_OFFSET, numPairs / 2);
  g_STAT_OFFSET++;
  {
    unsigned i;
    for (i = 0; i < numPairs; i += 2)
      printf("%2u %6u   | ", p->matches[i], p->matches[i + 1]);
  }
  #endif
  
  if (numPairs == 0)
    return 0;
  {
    unsigned len = p->matches[(size_t)numPairs - 2];
    if (len != p->numFastBytes)
      return len;
    {
      UInt32 numAvail = p->numAvail;
      if (numAvail > LZMA_MATCH_LEN_MAX)
        numAvail = LZMA_MATCH_LEN_MAX;
      {
        const Byte *p1 = p->matchFinder.GetPointerToCurrentPos(p->matchFinderObj) - 1;
        const Byte *p2 = p1 + len;
        ptrdiff_t dif = (ptrdiff_t)-1 - p->matches[(size_t)numPairs - 1];
        const Byte *lim = p1 + numAvail;
        for (; p2 != lim && *p2 == p2[dif]; p2++)
        {}
        return (unsigned)(p2 - p1);
      }
    }
  }
}