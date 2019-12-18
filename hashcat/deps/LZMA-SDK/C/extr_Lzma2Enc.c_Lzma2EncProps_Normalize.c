#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int UInt64 ;
typedef  int UInt32 ;
struct TYPE_5__ {int numThreads; int reduceSize; int dictSize; } ;
struct TYPE_6__ {int numBlockThreads_Max; int numTotalThreads; int blockSize; int numBlockThreads_Reduced; TYPE_1__ lzmaProps; } ;
typedef  scalar_t__ Int64 ;
typedef  TYPE_1__ CLzmaEncProps ;
typedef  TYPE_2__ CLzma2EncProps ;

/* Variables and functions */
 int LZMA2_ENC_PROPS__BLOCK_SIZE__AUTO ; 
 int LZMA2_ENC_PROPS__BLOCK_SIZE__SOLID ; 
 int /*<<< orphan*/  LzmaEncProps_Normalize (TYPE_1__*) ; 
 int MTCODER__THREADS_MAX ; 

void Lzma2EncProps_Normalize(CLzma2EncProps *p)
{
  UInt64 fileSize;
  int t1, t1n, t2, t2r, t3;
  {
    CLzmaEncProps lzmaProps = p->lzmaProps;
    LzmaEncProps_Normalize(&lzmaProps);
    t1n = lzmaProps.numThreads;
  }

  t1 = p->lzmaProps.numThreads;
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

  p->lzmaProps.numThreads = t1;

  t2r = t2;

  fileSize = p->lzmaProps.reduceSize;

  if (   p->blockSize != LZMA2_ENC_PROPS__BLOCK_SIZE__SOLID
      && p->blockSize != LZMA2_ENC_PROPS__BLOCK_SIZE__AUTO
      && (p->blockSize < fileSize || fileSize == (UInt64)(Int64)-1))
    p->lzmaProps.reduceSize = p->blockSize;

  LzmaEncProps_Normalize(&p->lzmaProps);

  p->lzmaProps.reduceSize = fileSize;

  t1 = p->lzmaProps.numThreads;

  if (p->blockSize == LZMA2_ENC_PROPS__BLOCK_SIZE__SOLID)
  {
    t2r = t2 = 1;
    t3 = t1;
  }
  else if (p->blockSize == LZMA2_ENC_PROPS__BLOCK_SIZE__AUTO && t2 <= 1)
  {
    /* if there is no block multi-threading, we use SOLID block */
    p->blockSize = LZMA2_ENC_PROPS__BLOCK_SIZE__SOLID;
  }
  else
  {
    if (p->blockSize == LZMA2_ENC_PROPS__BLOCK_SIZE__AUTO)
    {
      const UInt32 kMinSize = (UInt32)1 << 20;
      const UInt32 kMaxSize = (UInt32)1 << 28;
      const UInt32 dictSize = p->lzmaProps.dictSize;
      UInt64 blockSize = (UInt64)dictSize << 2;
      if (blockSize < kMinSize) blockSize = kMinSize;
      if (blockSize > kMaxSize) blockSize = kMaxSize;
      if (blockSize < dictSize) blockSize = dictSize;
      blockSize += (kMinSize - 1);
      blockSize &= ~(UInt64)(kMinSize - 1);
      p->blockSize = blockSize;
    }
    
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