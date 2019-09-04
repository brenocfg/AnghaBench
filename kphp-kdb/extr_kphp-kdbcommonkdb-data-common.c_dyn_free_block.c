#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  NX ;
typedef  int /*<<< orphan*/  MAGIC ;

/* Variables and functions */
 int /*<<< orphan*/  DYN_FREE_MAGIC ; 
 int /*<<< orphan*/ * FreeBlocks ; 
 int /*<<< orphan*/ * FreeBlocksAligned ; 
 int /*<<< orphan*/ * FreeCnt ; 
 int PTR_INTS ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static inline void dyn_free_block (void *p, int words) {
  assert (words >= PTR_INTS);
  FreeCnt[words]++;
  if (!((long) p & 7)) { 
    NX(p) = FreeBlocksAligned[words];
    FreeBlocksAligned[words] = p;
  } else {
    NX(p) = FreeBlocks[words];
    FreeBlocks[words] = p;
  }
  if (words > PTR_INTS) {
    MAGIC(p) = DYN_FREE_MAGIC;
  }
}