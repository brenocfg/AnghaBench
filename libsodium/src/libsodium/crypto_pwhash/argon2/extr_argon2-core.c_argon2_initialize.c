#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_8__ {int segment_length; int /*<<< orphan*/  type; int /*<<< orphan*/  memory_blocks; int /*<<< orphan*/  region; int /*<<< orphan*/ * pseudo_rands; } ;
typedef  TYPE_1__ argon2_instance_t ;
struct TYPE_9__ {int /*<<< orphan*/  flags; } ;
typedef  TYPE_2__ argon2_context ;

/* Variables and functions */
 int ARGON2_INCORRECT_PARAMETER ; 
 int ARGON2_MEMORY_ALLOCATION_ERROR ; 
 int ARGON2_OK ; 
 int ARGON2_PREHASH_DIGEST_LENGTH ; 
 int ARGON2_PREHASH_SEED_LENGTH ; 
 int allocate_memory (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  argon2_fill_first_blocks (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  argon2_free_instance (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  argon2_initial_hash (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  sodium_memzero (int /*<<< orphan*/ *,int) ; 

int
argon2_initialize(argon2_instance_t *instance, argon2_context *context)
{
    uint8_t blockhash[ARGON2_PREHASH_SEED_LENGTH];
    int     result = ARGON2_OK;

    if (instance == NULL || context == NULL) {
        return ARGON2_INCORRECT_PARAMETER;
    }

    /* 1. Memory allocation */

    if ((instance->pseudo_rands = (uint64_t *)
         malloc(sizeof(uint64_t) * instance->segment_length)) == NULL) {
        return ARGON2_MEMORY_ALLOCATION_ERROR;
    }

    result = allocate_memory(&(instance->region), instance->memory_blocks);
    if (ARGON2_OK != result) {
        argon2_free_instance(instance, context->flags);
        return result;
    }

    /* 2. Initial hashing */
    /* H_0 + 8 extra bytes to produce the first blocks */
    /* uint8_t blockhash[ARGON2_PREHASH_SEED_LENGTH]; */
    /* Hashing all inputs */
    argon2_initial_hash(blockhash, context, instance->type);
    /* Zeroing 8 extra bytes */
    sodium_memzero(blockhash + ARGON2_PREHASH_DIGEST_LENGTH,
                   ARGON2_PREHASH_SEED_LENGTH - ARGON2_PREHASH_DIGEST_LENGTH);

    /* 3. Creating first blocks, we always have at least two blocks in a slice
     */
    argon2_fill_first_blocks(blockhash, instance);
    /* Clearing the hash */
    sodium_memzero(blockhash, ARGON2_PREHASH_SEED_LENGTH);

    return ARGON2_OK;
}