#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_4__ {int /*<<< orphan*/  type_code_calculator; } ;
struct TYPE_5__ {size_t alphabet_size_; size_t num_block_types_; size_t num_blocks_; scalar_t__ bits_; scalar_t__ depths_; scalar_t__ entropy_ix_; int /*<<< orphan*/  block_len_; scalar_t__ block_ix_; TYPE_1__ block_split_code_; int /*<<< orphan*/  const* block_lengths_; int /*<<< orphan*/  const* block_types_; } ;
typedef  TYPE_2__ BlockEncoder ;

/* Variables and functions */
 int /*<<< orphan*/  InitBlockTypeCodeCalculator (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void InitBlockEncoder(BlockEncoder* self, size_t alphabet_size,
    size_t num_block_types, const uint8_t* block_types,
    const uint32_t* block_lengths, const size_t num_blocks) {
  self->alphabet_size_ = alphabet_size;
  self->num_block_types_ = num_block_types;
  self->block_types_ = block_types;
  self->block_lengths_ = block_lengths;
  self->num_blocks_ = num_blocks;
  InitBlockTypeCodeCalculator(&self->block_split_code_.type_code_calculator);
  self->block_ix_ = 0;
  self->block_len_ = num_blocks == 0 ? 0 : block_lengths[0];
  self->entropy_ix_ = 0;
  self->depths_ = 0;
  self->bits_ = 0;
}