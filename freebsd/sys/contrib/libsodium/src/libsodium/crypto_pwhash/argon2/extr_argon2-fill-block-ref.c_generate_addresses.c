#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  size_t uint32_t ;
struct TYPE_10__ {int /*<<< orphan*/ * v; } ;
typedef  TYPE_1__ block ;
struct TYPE_11__ {int /*<<< orphan*/  slice; int /*<<< orphan*/  lane; int /*<<< orphan*/  pass; } ;
typedef  TYPE_2__ argon2_position_t ;
struct TYPE_12__ {size_t segment_length; int /*<<< orphan*/  type; int /*<<< orphan*/  passes; int /*<<< orphan*/  memory_blocks; } ;
typedef  TYPE_3__ argon2_instance_t ;

/* Variables and functions */
 size_t ARGON2_ADDRESSES_IN_BLOCK ; 
 int /*<<< orphan*/  fill_block_with_xor (TYPE_1__*,TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  init_block_value (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
generate_addresses(const argon2_instance_t *instance,
                   const argon2_position_t *position, uint64_t *pseudo_rands)
{
    block    zero_block, input_block, address_block, tmp_block;
    uint32_t i;

    init_block_value(&zero_block, 0);
    init_block_value(&input_block, 0);

    if (instance != NULL && position != NULL) {
        input_block.v[0] = position->pass;
        input_block.v[1] = position->lane;
        input_block.v[2] = position->slice;
        input_block.v[3] = instance->memory_blocks;
        input_block.v[4] = instance->passes;
        input_block.v[5] = instance->type;

        for (i = 0; i < instance->segment_length; ++i) {
            if (i % ARGON2_ADDRESSES_IN_BLOCK == 0) {
                input_block.v[6]++;
                init_block_value(&tmp_block, 0);
                init_block_value(&address_block, 0);
                fill_block_with_xor(&zero_block, &input_block, &tmp_block);
                fill_block_with_xor(&zero_block, &tmp_block, &address_block);
            }

            pseudo_rands[i] = address_block.v[i % ARGON2_ADDRESSES_IN_BLOCK];
        }
    }
}