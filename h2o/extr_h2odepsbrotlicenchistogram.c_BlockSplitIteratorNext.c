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
struct TYPE_5__ {scalar_t__ length_; size_t idx_; TYPE_1__* split_; int /*<<< orphan*/  type_; } ;
struct TYPE_4__ {scalar_t__* lengths; int /*<<< orphan*/ * types; } ;
typedef  TYPE_2__ BlockSplitIterator ;

/* Variables and functions */

__attribute__((used)) static void BlockSplitIteratorNext(BlockSplitIterator* self) {
  if (self->length_ == 0) {
    ++self->idx_;
    self->type_ = self->split_->types[self->idx_];
    self->length_ = self->split_->lengths[self->idx_];
  }
  --self->length_;
}