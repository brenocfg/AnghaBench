#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UInt64 ;
struct TYPE_7__ {scalar_t__ reduceSize; } ;
struct TYPE_9__ {scalar_t__ numTotalThreads; scalar_t__ blockSize; int numBlockThreads_Reduced; int numBlockThreads_Max; TYPE_1__ lzmaProps; } ;
struct TYPE_8__ {scalar_t__ blockSize; scalar_t__ reduceSize; int numBlockThreads_Reduced; int numBlockThreads_Max; scalar_t__ numTotalThreads; TYPE_3__ lzma2Props; } ;
typedef  scalar_t__ Int64 ;
typedef  TYPE_2__ CXzProps ;
typedef  TYPE_3__ CLzma2EncProps ;

/* Variables and functions */
 scalar_t__ LZMA2_ENC_PROPS__BLOCK_SIZE__AUTO ; 
 scalar_t__ LZMA2_ENC_PROPS__BLOCK_SIZE__SOLID ; 
 int /*<<< orphan*/  Lzma2EncProps_Normalize (TYPE_3__*) ; 
 scalar_t__ XZ_PROPS__BLOCK_SIZE__SOLID ; 
 int /*<<< orphan*/  XzEncProps_Normalize_Fixed (TYPE_2__*) ; 

__attribute__((used)) static void XzProps_Normalize(CXzProps *p)
{
  /* we normalize xzProps properties, but we normalize only some of CXzProps::lzma2Props properties.
     Lzma2Enc_SetProps() will normalize lzma2Props later. */
  
  if (p->blockSize == XZ_PROPS__BLOCK_SIZE__SOLID)
  {
    p->lzma2Props.lzmaProps.reduceSize = p->reduceSize;
    p->numBlockThreads_Reduced = 1;
    p->numBlockThreads_Max = 1;
    if (p->lzma2Props.numTotalThreads <= 0)
      p->lzma2Props.numTotalThreads = p->numTotalThreads;
    return;
  }
  else
  {
    CLzma2EncProps *lzma2 = &p->lzma2Props;
    if (p->blockSize == LZMA2_ENC_PROPS__BLOCK_SIZE__AUTO)
    {
      // xz-auto
      p->lzma2Props.lzmaProps.reduceSize = p->reduceSize;

      if (lzma2->blockSize == LZMA2_ENC_PROPS__BLOCK_SIZE__SOLID)
      {
        // if (xz-auto && lzma2-solid) - we use solid for both
        p->blockSize = XZ_PROPS__BLOCK_SIZE__SOLID;
        p->numBlockThreads_Reduced = 1;
        p->numBlockThreads_Max = 1;
        if (p->lzma2Props.numTotalThreads <= 0)
          p->lzma2Props.numTotalThreads = p->numTotalThreads;
      }
      else
      {
        // if (xz-auto && (lzma2-auto || lzma2-fixed_)
        //   we calculate block size for lzma2 and use that block size for xz, lzma2 uses single-chunk per block
        CLzma2EncProps tp = p->lzma2Props;
        if (tp.numTotalThreads <= 0)
          tp.numTotalThreads = p->numTotalThreads;
        
        Lzma2EncProps_Normalize(&tp);
        
        p->blockSize = tp.blockSize; // fixed or solid
        p->numBlockThreads_Reduced = tp.numBlockThreads_Reduced;
        p->numBlockThreads_Max = tp.numBlockThreads_Max;
        if (lzma2->blockSize == LZMA2_ENC_PROPS__BLOCK_SIZE__AUTO)
          lzma2->blockSize = tp.blockSize; // fixed or solid, LZMA2_ENC_PROPS__BLOCK_SIZE__SOLID
        if (lzma2->lzmaProps.reduceSize > tp.blockSize && tp.blockSize != LZMA2_ENC_PROPS__BLOCK_SIZE__SOLID)
          lzma2->lzmaProps.reduceSize = tp.blockSize;
        lzma2->numBlockThreads_Reduced = 1;
        lzma2->numBlockThreads_Max = 1;
        return;
      }
    }
    else
    {
      // xz-fixed
      // we can use xz::reduceSize or xz::blockSize as base for lzmaProps::reduceSize
      
      p->lzma2Props.lzmaProps.reduceSize = p->reduceSize;
      {
        UInt64 r = p->reduceSize;
        if (r > p->blockSize || r == (UInt64)(Int64)-1)
          r = p->blockSize;
        lzma2->lzmaProps.reduceSize = r;
      }
      if (lzma2->blockSize == LZMA2_ENC_PROPS__BLOCK_SIZE__AUTO)
        lzma2->blockSize = LZMA2_ENC_PROPS__BLOCK_SIZE__SOLID;
      else if (lzma2->blockSize > p->blockSize && lzma2->blockSize != LZMA2_ENC_PROPS__BLOCK_SIZE__SOLID)
        lzma2->blockSize = p->blockSize;
      
      XzEncProps_Normalize_Fixed(p);
    }
  }
}