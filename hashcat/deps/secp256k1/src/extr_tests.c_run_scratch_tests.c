#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int alloc_size; } ;
typedef  TYPE_1__ secp256k1_scratch_space ;
struct TYPE_17__ {int /*<<< orphan*/  error_callback; } ;
typedef  TYPE_2__ secp256k1_context ;
typedef  int /*<<< orphan*/  local_scratch ;
typedef  int int32_t ;

/* Variables and functions */
 int ALIGNMENT ; 
 int /*<<< orphan*/  CHECK (int) ; 
 int /*<<< orphan*/  SECP256K1_CONTEXT_NONE ; 
 int /*<<< orphan*/  counting_illegal_callback_fn ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 TYPE_2__* secp256k1_context_create (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  secp256k1_context_destroy (TYPE_2__*) ; 
 int /*<<< orphan*/  secp256k1_context_set_error_callback (TYPE_2__*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  secp256k1_context_set_illegal_callback (TYPE_2__*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/ * secp256k1_scratch_alloc (int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 int /*<<< orphan*/  secp256k1_scratch_apply_checkpoint (int /*<<< orphan*/ *,TYPE_1__*,size_t) ; 
 size_t secp256k1_scratch_checkpoint (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int secp256k1_scratch_max_allocation (int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 TYPE_1__* secp256k1_scratch_space_create (TYPE_2__*,int) ; 
 int /*<<< orphan*/  secp256k1_scratch_space_destroy (TYPE_2__*,TYPE_1__*) ; 

void run_scratch_tests(void) {
    const size_t adj_alloc = ((500 + ALIGNMENT - 1) / ALIGNMENT) * ALIGNMENT;

    int32_t ecount = 0;
    size_t checkpoint;
    size_t checkpoint_2;
    secp256k1_context *none = secp256k1_context_create(SECP256K1_CONTEXT_NONE);
    secp256k1_scratch_space *scratch;
    secp256k1_scratch_space local_scratch;

    /* Test public API */
    secp256k1_context_set_illegal_callback(none, counting_illegal_callback_fn, &ecount);
    secp256k1_context_set_error_callback(none, counting_illegal_callback_fn, &ecount);

    scratch = secp256k1_scratch_space_create(none, 1000);
    CHECK(scratch != NULL);
    CHECK(ecount == 0);

    /* Test internal API */
    CHECK(secp256k1_scratch_max_allocation(&none->error_callback, scratch, 0) == 1000);
    CHECK(secp256k1_scratch_max_allocation(&none->error_callback, scratch, 1) == 1000 - (ALIGNMENT - 1));
    CHECK(scratch->alloc_size == 0);
    CHECK(scratch->alloc_size % ALIGNMENT == 0);

    /* Allocating 500 bytes succeeds */
    checkpoint = secp256k1_scratch_checkpoint(&none->error_callback, scratch);
    CHECK(secp256k1_scratch_alloc(&none->error_callback, scratch, 500) != NULL);
    CHECK(secp256k1_scratch_max_allocation(&none->error_callback, scratch, 0) == 1000 - adj_alloc);
    CHECK(secp256k1_scratch_max_allocation(&none->error_callback, scratch, 1) == 1000 - adj_alloc - (ALIGNMENT - 1));
    CHECK(scratch->alloc_size != 0);
    CHECK(scratch->alloc_size % ALIGNMENT == 0);

    /* Allocating another 500 bytes fails */
    CHECK(secp256k1_scratch_alloc(&none->error_callback, scratch, 500) == NULL);
    CHECK(secp256k1_scratch_max_allocation(&none->error_callback, scratch, 0) == 1000 - adj_alloc);
    CHECK(secp256k1_scratch_max_allocation(&none->error_callback, scratch, 1) == 1000 - adj_alloc - (ALIGNMENT - 1));
    CHECK(scratch->alloc_size != 0);
    CHECK(scratch->alloc_size % ALIGNMENT == 0);

    /* ...but it succeeds once we apply the checkpoint to undo it */
    secp256k1_scratch_apply_checkpoint(&none->error_callback, scratch, checkpoint);
    CHECK(scratch->alloc_size == 0);
    CHECK(secp256k1_scratch_max_allocation(&none->error_callback, scratch, 0) == 1000);
    CHECK(secp256k1_scratch_alloc(&none->error_callback, scratch, 500) != NULL);
    CHECK(scratch->alloc_size != 0);

    /* try to apply a bad checkpoint */
    checkpoint_2 = secp256k1_scratch_checkpoint(&none->error_callback, scratch);
    secp256k1_scratch_apply_checkpoint(&none->error_callback, scratch, checkpoint);
    CHECK(ecount == 0);
    secp256k1_scratch_apply_checkpoint(&none->error_callback, scratch, checkpoint_2); /* checkpoint_2 is after checkpoint */
    CHECK(ecount == 1);
    secp256k1_scratch_apply_checkpoint(&none->error_callback, scratch, (size_t) -1); /* this is just wildly invalid */
    CHECK(ecount == 2);

    /* try to use badly initialized scratch space */
    secp256k1_scratch_space_destroy(none, scratch);
    memset(&local_scratch, 0, sizeof(local_scratch));
    scratch = &local_scratch;
    CHECK(!secp256k1_scratch_max_allocation(&none->error_callback, scratch, 0));
    CHECK(ecount == 3);
    CHECK(secp256k1_scratch_alloc(&none->error_callback, scratch, 500) == NULL);
    CHECK(ecount == 4);
    secp256k1_scratch_space_destroy(none, scratch);
    CHECK(ecount == 5);

    /* cleanup */
    secp256k1_scratch_space_destroy(none, NULL); /* no-op */
    secp256k1_context_destroy(none);
}