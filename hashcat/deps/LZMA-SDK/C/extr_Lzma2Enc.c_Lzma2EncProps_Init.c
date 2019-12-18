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
struct TYPE_3__ {int numBlockThreads_Reduced; int numBlockThreads_Max; int numTotalThreads; int /*<<< orphan*/  blockSize; int /*<<< orphan*/  lzmaProps; } ;
typedef  TYPE_1__ CLzma2EncProps ;

/* Variables and functions */
 int /*<<< orphan*/  LZMA2_ENC_PROPS__BLOCK_SIZE__AUTO ; 
 int /*<<< orphan*/  LzmaEncProps_Init (int /*<<< orphan*/ *) ; 

void Lzma2EncProps_Init(CLzma2EncProps *p)
{
  LzmaEncProps_Init(&p->lzmaProps);
  p->blockSize = LZMA2_ENC_PROPS__BLOCK_SIZE__AUTO;
  p->numBlockThreads_Reduced = -1;
  p->numBlockThreads_Max = -1;
  p->numTotalThreads = -1;
}