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
struct TYPE_3__ {int decodeOnlyOneBlock; scalar_t__ pos; int /*<<< orphan*/  state; int /*<<< orphan*/  sha; scalar_t__ numBlocks; scalar_t__ indexSize; } ;
typedef  TYPE_1__ CXzUnpacker ;

/* Variables and functions */
 int /*<<< orphan*/  Sha256_Init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XZ_STATE_BLOCK_HEADER ; 

void XzUnpacker_PrepareToRandomBlockDecoding(CXzUnpacker *p)
{
  p->indexSize = 0;
  p->numBlocks = 0;
  Sha256_Init(&p->sha);
  p->state = XZ_STATE_BLOCK_HEADER;
  p->pos = 0;
  p->decodeOnlyOneBlock = 1;
}