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
typedef  unsigned int UInt32 ;
struct TYPE_3__ {int level; int dictSize; int reduceSize; int lc; scalar_t__ lp; int pb; int algo; int fb; int btMode; int numHashBytes; int mc; int numThreads; } ;
typedef  TYPE_1__ CLzmaEncProps ;

/* Variables and functions */

void LzmaEncProps_Normalize(CLzmaEncProps *p)
{
  int level = p->level;
  if (level < 0) level = 5;
  p->level = level;
  
  if (p->dictSize == 0) p->dictSize = (level <= 5 ? (1 << (level * 2 + 14)) : (level <= 7 ? (1 << 25) : (1 << 26)));
  if (p->dictSize > p->reduceSize)
  {
    unsigned i;
    UInt32 reduceSize = (UInt32)p->reduceSize;
    for (i = 11; i <= 30; i++)
    {
      if (reduceSize <= ((UInt32)2 << i)) { p->dictSize = ((UInt32)2 << i); break; }
      if (reduceSize <= ((UInt32)3 << i)) { p->dictSize = ((UInt32)3 << i); break; }
    }
  }

  if (p->lc < 0) p->lc = 3;
  if (p->lp < 0) p->lp = 0;
  if (p->pb < 0) p->pb = 2;

  if (p->algo < 0) p->algo = (level < 5 ? 0 : 1);
  if (p->fb < 0) p->fb = (level < 7 ? 32 : 64);
  if (p->btMode < 0) p->btMode = (p->algo == 0 ? 0 : 1);
  if (p->numHashBytes < 0) p->numHashBytes = 4;
  if (p->mc == 0) p->mc = (16 + (p->fb >> 1)) >> (p->btMode ? 0 : 1);
  
  if (p->numThreads < 0)
    p->numThreads =
      #ifndef _7ZIP_ST
      ((p->btMode && p->algo) ? 2 : 1);
      #else
      1;
      #endif
}