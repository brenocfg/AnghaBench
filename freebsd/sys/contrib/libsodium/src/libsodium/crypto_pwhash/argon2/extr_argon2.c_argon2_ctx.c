#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  scalar_t__ argon2_type ;
struct TYPE_10__ {int passes; unsigned int current_pass; int memory_blocks; int segment_length; int lane_length; int lanes; scalar_t__ type; int /*<<< orphan*/  threads; int /*<<< orphan*/ * region; } ;
typedef  TYPE_1__ argon2_instance_t ;
struct TYPE_11__ {int m_cost; int lanes; int t_cost; int /*<<< orphan*/  threads; } ;
typedef  TYPE_2__ argon2_context ;

/* Variables and functions */
 int ARGON2_INCORRECT_TYPE ; 
 int ARGON2_OK ; 
 int ARGON2_SYNC_POINTS ; 
 scalar_t__ Argon2_i ; 
 scalar_t__ Argon2_id ; 
 int /*<<< orphan*/  fill_memory_blocks (TYPE_1__*,int) ; 
 int /*<<< orphan*/  finalize (TYPE_2__*,TYPE_1__*) ; 
 int initialize (TYPE_1__*,TYPE_2__*) ; 
 int validate_inputs (TYPE_2__*) ; 

int
argon2_ctx(argon2_context *context, argon2_type type)
{
    /* 1. Validate all inputs */
    int               result = validate_inputs(context);
    uint32_t          memory_blocks, segment_length;
    uint32_t          pass;
    argon2_instance_t instance;

    if (ARGON2_OK != result) {
        return result;
    }

    if (type != Argon2_id && type != Argon2_i) {
        return ARGON2_INCORRECT_TYPE;
    }

    /* 2. Align memory size */
    /* Minimum memory_blocks = 8L blocks, where L is the number of lanes */
    memory_blocks = context->m_cost;

    if (memory_blocks < 2 * ARGON2_SYNC_POINTS * context->lanes) {
        memory_blocks = 2 * ARGON2_SYNC_POINTS * context->lanes;
    }

    segment_length = memory_blocks / (context->lanes * ARGON2_SYNC_POINTS);
    /* Ensure that all segments have equal length */
    memory_blocks = segment_length * (context->lanes * ARGON2_SYNC_POINTS);

    instance.region         = NULL;
    instance.passes         = context->t_cost;
    instance.current_pass   = ~ 0U;
    instance.memory_blocks  = memory_blocks;
    instance.segment_length = segment_length;
    instance.lane_length    = segment_length * ARGON2_SYNC_POINTS;
    instance.lanes          = context->lanes;
    instance.threads        = context->threads;
    instance.type           = type;

    /* 3. Initialization: Hashing inputs, allocating memory, filling first
     * blocks
     */
    result = initialize(&instance, context);

    if (ARGON2_OK != result) {
        return result;
    }

    /* 4. Filling memory */
    for (pass = 0; pass < instance.passes; pass++) {
        fill_memory_blocks(&instance, pass);
    }

    /* 5. Finalization */
    finalize(context, &instance);

    return ARGON2_OK;
}