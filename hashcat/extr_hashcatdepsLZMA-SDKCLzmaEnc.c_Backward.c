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
typedef  int UInt32 ;
struct TYPE_5__ {unsigned int optEnd; int backRes; unsigned int optCur; TYPE_1__* opt; } ;
struct TYPE_4__ {int dist; int len; int extra; } ;
typedef  TYPE_2__ CLzmaEnc ;

/* Variables and functions */
 void* MARK_LIT ; 

__attribute__((used)) static unsigned Backward(CLzmaEnc *p, unsigned cur)
{
  unsigned wr = cur + 1;
  p->optEnd = wr;

  for (;;)
  {
    UInt32 dist = p->opt[cur].dist;
    UInt32 len = p->opt[cur].len;
    UInt32 extra = p->opt[cur].extra;
    cur -= len;

    if (extra)
    {
      wr--;
      p->opt[wr].len = len;
      cur -= extra;
      len = extra;
      if (extra == 1)
      {
        p->opt[wr].dist = dist;
        dist = MARK_LIT;
      }
      else
      {
        p->opt[wr].dist = 0;
        len--;
        wr--;
        p->opt[wr].dist = MARK_LIT;
        p->opt[wr].len = 1;
      }
    }

    if (cur == 0)
    {
      p->backRes = dist;
      p->optCur = wr;
      return len;
    }
    
    wr--;
    p->opt[wr].dist = dist;
    p->opt[wr].len = len;
  }
}