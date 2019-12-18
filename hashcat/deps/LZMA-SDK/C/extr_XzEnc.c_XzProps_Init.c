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
typedef  scalar_t__ UInt64 ;
struct TYPE_3__ {int numBlockThreads_Reduced; int numBlockThreads_Max; int numTotalThreads; int /*<<< orphan*/  lzma2Props; int /*<<< orphan*/  filterProps; scalar_t__ forceWriteSizesInHeader; scalar_t__ reduceSize; int /*<<< orphan*/  blockSize; int /*<<< orphan*/  checkId; } ;
typedef  scalar_t__ Int64 ;
typedef  TYPE_1__ CXzProps ;

/* Variables and functions */
 int /*<<< orphan*/  Lzma2EncProps_Init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XZ_CHECK_CRC32 ; 
 int /*<<< orphan*/  XZ_PROPS__BLOCK_SIZE__AUTO ; 
 int /*<<< orphan*/  XzFilterProps_Init (int /*<<< orphan*/ *) ; 

void XzProps_Init(CXzProps *p)
{
  p->checkId = XZ_CHECK_CRC32;
  p->blockSize = XZ_PROPS__BLOCK_SIZE__AUTO;
  p->numBlockThreads_Reduced = -1;
  p->numBlockThreads_Max = -1;
  p->numTotalThreads = -1;
  p->reduceSize = (UInt64)(Int64)-1;
  p->forceWriteSizesInHeader = 0;
  // p->forceWriteSizesInHeader = 1;

  XzFilterProps_Init(&p->filterProps);
  Lzma2EncProps_Init(&p->lzma2Props);
}