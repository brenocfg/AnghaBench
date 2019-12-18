#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {size_t curr_histogram_ix_; scalar_t__ block_size_; scalar_t__ target_block_size_; int /*<<< orphan*/ * histograms_; } ;
typedef  int /*<<< orphan*/  MemoryManager ;
typedef  TYPE_1__ ContextBlockSplitter ;

/* Variables and functions */
 int /*<<< orphan*/  BROTLI_FALSE ; 
 scalar_t__ BROTLI_IS_OOM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ContextBlockSplitterFinishBlock (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HistogramAddLiteral (int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static void ContextBlockSplitterAddSymbol(
    ContextBlockSplitter* self, MemoryManager* m,
    size_t symbol, size_t context) {
  HistogramAddLiteral(&self->histograms_[self->curr_histogram_ix_ + context],
      symbol);
  ++self->block_size_;
  if (self->block_size_ == self->target_block_size_) {
    ContextBlockSplitterFinishBlock(self, m, /* is_final = */ BROTLI_FALSE);
    if (BROTLI_IS_OOM(m)) return;
  }
}