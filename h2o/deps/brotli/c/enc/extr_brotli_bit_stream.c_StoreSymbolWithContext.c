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
typedef  scalar_t__ uint8_t ;
typedef  size_t uint32_t ;
struct TYPE_3__ {scalar_t__ block_len_; size_t block_ix_; size_t* block_lengths_; size_t entropy_ix_; size_t alphabet_size_; int /*<<< orphan*/ * bits_; int /*<<< orphan*/ * depths_; int /*<<< orphan*/  block_split_code_; scalar_t__* block_types_; } ;
typedef  TYPE_1__ BlockEncoder ;

/* Variables and functions */
 int /*<<< orphan*/  BrotliWriteBits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t*,scalar_t__*) ; 
 int /*<<< orphan*/  StoreBlockSwitch (int /*<<< orphan*/ *,size_t,scalar_t__,int /*<<< orphan*/ ,size_t*,scalar_t__*) ; 

__attribute__((used)) static void StoreSymbolWithContext(BlockEncoder* self, size_t symbol,
    size_t context, const uint32_t* context_map, size_t* storage_ix,
    uint8_t* storage, const size_t context_bits) {
  if (self->block_len_ == 0) {
    size_t block_ix = ++self->block_ix_;
    uint32_t block_len = self->block_lengths_[block_ix];
    uint8_t block_type = self->block_types_[block_ix];
    self->block_len_ = block_len;
    self->entropy_ix_ = (size_t)block_type << context_bits;
    StoreBlockSwitch(&self->block_split_code_, block_len, block_type, 0,
        storage_ix, storage);
  }
  --self->block_len_;
  {
    size_t histo_ix = context_map[self->entropy_ix_ + context];
    size_t ix = histo_ix * self->alphabet_size_ + symbol;
    BrotliWriteBits(self->depths_[ix], self->bits_[ix], storage_ix, storage);
  }
}