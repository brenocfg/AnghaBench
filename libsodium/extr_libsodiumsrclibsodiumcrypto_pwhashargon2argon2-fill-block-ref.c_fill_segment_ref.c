#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  int uint32_t ;
struct TYPE_18__ {int* v; } ;
typedef  TYPE_2__ block ;
struct TYPE_19__ {scalar_t__ pass; int slice; int lane; int index; } ;
typedef  TYPE_3__ argon2_position_t ;
struct TYPE_20__ {scalar_t__ type; int* pseudo_rands; int lane_length; int segment_length; int lanes; TYPE_1__* region; } ;
typedef  TYPE_4__ argon2_instance_t ;
struct TYPE_17__ {TYPE_2__* memory; } ;

/* Variables and functions */
 int ARGON2_SYNC_POINTS ; 
 scalar_t__ Argon2_id ; 
 int /*<<< orphan*/  fill_block (TYPE_2__*,TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  fill_block_with_xor (TYPE_2__*,TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  generate_addresses (TYPE_4__ const*,TYPE_3__*,int*) ; 
 int index_alpha (TYPE_4__ const*,TYPE_3__*,int,int) ; 

void
fill_segment_ref(const argon2_instance_t *instance, argon2_position_t position)
{
    block    *ref_block = NULL, *curr_block = NULL;
    /* Pseudo-random values that determine the reference block position */
    uint64_t *pseudo_rands = NULL;
    uint64_t  pseudo_rand, ref_index, ref_lane;
    uint32_t  prev_offset, curr_offset;
    uint32_t  starting_index;
    uint32_t  i;
    int       data_independent_addressing = 1;

    if (instance == NULL) {
        return;
    }

    if (instance->type == Argon2_id &&
        (position.pass != 0 || position.slice >= ARGON2_SYNC_POINTS / 2)) {
        data_independent_addressing = 0;
    }

    pseudo_rands = instance->pseudo_rands;

    if (data_independent_addressing) {
        generate_addresses(instance, &position, pseudo_rands);
    }

    starting_index = 0;

    if ((0 == position.pass) && (0 == position.slice)) {
        starting_index = 2; /* we have already generated the first two blocks */
    }

    /* Offset of the current block */
    curr_offset = position.lane * instance->lane_length +
                  position.slice * instance->segment_length + starting_index;

    if (0 == curr_offset % instance->lane_length) {
        /* Last block in this lane */
        prev_offset = curr_offset + instance->lane_length - 1;
    } else {
        /* Previous block */
        prev_offset = curr_offset - 1;
    }

    for (i = starting_index; i < instance->segment_length;
         ++i, ++curr_offset, ++prev_offset) {
        /*1.1 Rotating prev_offset if needed */
        if (curr_offset % instance->lane_length == 1) {
            prev_offset = curr_offset - 1;
        }

        /* 1.2 Computing the index of the reference block */
        /* 1.2.1 Taking pseudo-random value from the previous block */
        if (data_independent_addressing) {
#pragma warning(push)
#pragma warning(disable : 6385)
            pseudo_rand = pseudo_rands[i];
#pragma warning(pop)
        } else {
            pseudo_rand = instance->region->memory[prev_offset].v[0];
        }

        /* 1.2.2 Computing the lane of the reference block */
        ref_lane = ((pseudo_rand >> 32)) % instance->lanes;

        if ((position.pass == 0) && (position.slice == 0)) {
            /* Can not reference other lanes yet */
            ref_lane = position.lane;
        }

        /* 1.2.3 Computing the number of possible reference block within the
         * lane.
         */
        position.index = i;
        ref_index = index_alpha(instance, &position, pseudo_rand & 0xFFFFFFFF,
                                ref_lane == position.lane);

        /* 2 Creating a new block */
        ref_block = instance->region->memory +
                    instance->lane_length * ref_lane + ref_index;
        curr_block = instance->region->memory + curr_offset;
        if (position.pass != 0) {
            fill_block_with_xor(instance->region->memory + prev_offset,
                                ref_block, curr_block);
        } else {
            fill_block(instance->region->memory + prev_offset, ref_block,
                       curr_block);
        }
    }
}