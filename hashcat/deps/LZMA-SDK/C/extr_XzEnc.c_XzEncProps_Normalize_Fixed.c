#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int UInt64 ;
struct TYPE_6__ {unsigned int reduceSize; } ;
struct TYPE_8__ {int numTotalThreads; TYPE_1__ lzmaProps; } ;
struct TYPE_7__ {int numTotalThreads; int numBlockThreads_Max; unsigned int reduceSize; unsigned int blockSize; int numBlockThreads_Reduced; TYPE_3__ lzma2Props; } ;
typedef  scalar_t__ Int64 ;
typedef  TYPE_2__ CXzProps ;
typedef  TYPE_3__ CLzma2EncProps ;

/* Variables and functions */
 int /*<<< orphan*/  Lzma2EncProps_Normalize (TYPE_3__*) ; 
 int MTCODER__THREADS_MAX ; 

__attribute__((used)) static void XzEncProps_Normalize_Fixed(CXzProps *p)
{
  UInt64 fileSize;
  int t1, t1n, t2, t2r, t3;
  {
    CLzma2EncProps tp = p->lzma2Props;
    if (tp.numTotalThreads <= 0)
      tp.numTotalThreads = p->numTotalThreads;
    Lzma2EncProps_Normalize(&tp);
    t1n = tp.numTotalThreads;
  }

  t1 = p->lzma2Props.numTotalThreads;
  t2 = p->numBlockThreads_Max;
  t3 = p->numTotalThreads;

  if (t2 > MTCODER__THREADS_MAX)
    t2 = MTCODER__THREADS_MAX;

  if (t3 <= 0)
  {
    if (t2 <= 0)
      t2 = 1;
    t3 = t1n * t2;
  }
  else if (t2 <= 0)
  {
    t2 = t3 / t1n;
    if (t2 == 0)
    {
      t1 = 1;
      t2 = t3;
    }
    if (t2 > MTCODER__THREADS_MAX)
      t2 = MTCODER__THREADS_MAX;
  }
  else if (t1 <= 0)
  {
    t1 = t3 / t2;
    if (t1 == 0)
      t1 = 1;
  }
  else
    t3 = t1n * t2;

  p->lzma2Props.numTotalThreads = t1;

  t2r = t2;

  fileSize = p->reduceSize;

  if ((p->blockSize < fileSize || fileSize == (UInt64)(Int64)-1))
    p->lzma2Props.lzmaProps.reduceSize = p->blockSize;

  Lzma2EncProps_Normalize(&p->lzma2Props);

  t1 = p->lzma2Props.numTotalThreads;

  {
    if (t2 > 1 && fileSize != (UInt64)(Int64)-1)
    {
      UInt64 numBlocks = fileSize / p->blockSize;
      if (numBlocks * p->blockSize != fileSize)
        numBlocks++;
      if (numBlocks < (unsigned)t2)
      {
        t2r = (unsigned)numBlocks;
        if (t2r == 0)
          t2r = 1;
        t3 = t1 * t2r;
      }
    }
  }
  
  p->numBlockThreads_Max = t2;
  p->numBlockThreads_Reduced = t2r;
  p->numTotalThreads = t3;
}