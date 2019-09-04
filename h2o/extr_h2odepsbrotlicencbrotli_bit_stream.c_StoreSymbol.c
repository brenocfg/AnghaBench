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
typedef  int uint8_t ;
typedef  scalar_t__ uint32_t ;
struct TYPE_3__ {scalar_t__ block_len_; size_t block_ix_; scalar_t__* block_lengths_; int* block_types_; int entropy_ix_; int alphabet_size_; int /*<<< orphan*/ * bits_; int /*<<< orphan*/ * depths_; int /*<<< orphan*/  block_split_code_; } ;
typedef  TYPE_1__ BlockEncoder ;

/* Variables and functions */
 int /*<<< orphan*/  BrotliWriteBits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t*,int*) ; 
 int /*<<< orphan*/  StoreBlockSwitch (int /*<<< orphan*/ *,scalar_t__,int,int /*<<< orphan*/ ,size_t*,int*) ; 

__attribute__((used)) static void StoreSymbol(BlockEncoder* self, size_t symbol, size_t* storage_ix,
    uint8_t* storage) {
  if (self->block_len_ == 0) {
    size_t block_ix = ++self->block_ix_;
    uint32_t block_len = self->block_lengths_[block_ix];
    uint8_t block_type = self->block_types_[block_ix];
    self->block_len_ = block_len;
    self->entropy_ix_ = block_type * self->alphabet_size_;
    StoreBlockSwitch(&self->block_split_code_, block_len, block_type, 0,
        storage_ix, storage);
  }
  --self->block_len_;
  {
    size_t ix = self->entropy_ix_ + symbol;
    BrotliWriteBits(self->depths_[ix], self->bits_[ix], storage_ix, storage);
  }
}