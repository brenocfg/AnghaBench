#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/ * htrees; int /*<<< orphan*/ * codes; } ;
struct TYPE_7__ {int /*<<< orphan*/ * htrees; int /*<<< orphan*/ * codes; } ;
struct TYPE_6__ {int /*<<< orphan*/ * htrees; int /*<<< orphan*/ * codes; } ;
struct TYPE_9__ {unsigned int* block_length; int* num_block_types; int* block_type_rb; TYPE_3__ distance_hgroup; TYPE_2__ insert_copy_hgroup; TYPE_1__ literal_hgroup; int /*<<< orphan*/ * context_lookup2; int /*<<< orphan*/ * context_lookup1; scalar_t__ dist_htree_index; int /*<<< orphan*/ * dist_context_map_slice; int /*<<< orphan*/ * literal_htree; int /*<<< orphan*/ * context_map_slice; int /*<<< orphan*/ * dist_context_map; int /*<<< orphan*/ * context_modes; int /*<<< orphan*/ * context_map; scalar_t__ meta_block_remaining_len; } ;
typedef  TYPE_4__ BrotliDecoderState ;

/* Variables and functions */

void BrotliDecoderStateMetablockBegin(BrotliDecoderState* s) {
  s->meta_block_remaining_len = 0;
  s->block_length[0] = 1U << 28;
  s->block_length[1] = 1U << 28;
  s->block_length[2] = 1U << 28;
  s->num_block_types[0] = 1;
  s->num_block_types[1] = 1;
  s->num_block_types[2] = 1;
  s->block_type_rb[0] = 1;
  s->block_type_rb[1] = 0;
  s->block_type_rb[2] = 1;
  s->block_type_rb[3] = 0;
  s->block_type_rb[4] = 1;
  s->block_type_rb[5] = 0;
  s->context_map = NULL;
  s->context_modes = NULL;
  s->dist_context_map = NULL;
  s->context_map_slice = NULL;
  s->literal_htree = NULL;
  s->dist_context_map_slice = NULL;
  s->dist_htree_index = 0;
  s->context_lookup1 = NULL;
  s->context_lookup2 = NULL;
  s->literal_hgroup.codes = NULL;
  s->literal_hgroup.htrees = NULL;
  s->insert_copy_hgroup.codes = NULL;
  s->insert_copy_hgroup.htrees = NULL;
  s->distance_hgroup.codes = NULL;
  s->distance_hgroup.htrees = NULL;
}