#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct TYPE_12__ {int /*<<< orphan*/ * v; } ;
typedef  TYPE_2__ block ;
struct TYPE_13__ {int lane_length; int lanes; TYPE_1__* region; } ;
typedef  TYPE_3__ argon2_instance_t ;
struct TYPE_14__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  outlen; int /*<<< orphan*/  out; } ;
typedef  TYPE_4__ argon2_context ;
struct TYPE_11__ {int memory; } ;

/* Variables and functions */
 int ARGON2_BLOCK_SIZE ; 
 int /*<<< orphan*/  argon2_free_instance (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blake2b_long (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  copy_block (TYPE_2__*,int) ; 
 int /*<<< orphan*/  sodium_memzero (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  store_block (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  xor_block (TYPE_2__*,int) ; 

void
argon2_finalize(const argon2_context *context, argon2_instance_t *instance)
{
    if (context != NULL && instance != NULL) {
        block    blockhash;
        uint32_t l;

        copy_block(&blockhash,
                   instance->region->memory + instance->lane_length - 1);

        /* XOR the last blocks */
        for (l = 1; l < instance->lanes; ++l) {
            uint32_t last_block_in_lane =
                l * instance->lane_length + (instance->lane_length - 1);
            xor_block(&blockhash,
                      instance->region->memory + last_block_in_lane);
        }

        /* Hash the result */
        {
            uint8_t blockhash_bytes[ARGON2_BLOCK_SIZE];
            store_block(blockhash_bytes, &blockhash);
            blake2b_long(context->out, context->outlen, blockhash_bytes,
                         ARGON2_BLOCK_SIZE);
            sodium_memzero(blockhash.v,
                           ARGON2_BLOCK_SIZE); /* clear blockhash */
            sodium_memzero(blockhash_bytes,
                           ARGON2_BLOCK_SIZE); /* clear blockhash_bytes */
        }

        argon2_free_instance(instance, context->flags);
    }
}