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
struct TYPE_3__ {int /*<<< orphan*/  ecmult_ctx; int /*<<< orphan*/  ecmult_gen_ctx; int /*<<< orphan*/  illegal_callback; int /*<<< orphan*/  error_callback; } ;
typedef  TYPE_1__ secp256k1_context ;

/* Variables and functions */
 scalar_t__ EXPECT (int,int /*<<< orphan*/ ) ; 
 unsigned int SECP256K1_FLAGS_BIT_CONTEXT_SIGN ; 
 unsigned int SECP256K1_FLAGS_BIT_CONTEXT_VERIFY ; 
 unsigned int SECP256K1_FLAGS_TYPE_CONTEXT ; 
 unsigned int SECP256K1_FLAGS_TYPE_MASK ; 
 int /*<<< orphan*/  VERIFY_CHECK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  default_error_callback ; 
 int /*<<< orphan*/  default_illegal_callback ; 
 scalar_t__ manual_alloc (void**,int,void* const,size_t) ; 
 int /*<<< orphan*/  secp256k1_callback_call (int /*<<< orphan*/ *,char*) ; 
 size_t secp256k1_context_preallocated_size (unsigned int) ; 
 int /*<<< orphan*/  secp256k1_ecmult_context_build (int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  secp256k1_ecmult_context_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  secp256k1_ecmult_gen_context_build (int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  secp256k1_ecmult_gen_context_init (int /*<<< orphan*/ *) ; 

secp256k1_context* secp256k1_context_preallocated_create(void* prealloc, unsigned int flags) {
    void* const base = prealloc;
    size_t prealloc_size;
    secp256k1_context* ret;

    VERIFY_CHECK(prealloc != NULL);
    prealloc_size = secp256k1_context_preallocated_size(flags);
    ret = (secp256k1_context*)manual_alloc(&prealloc, sizeof(secp256k1_context), base, prealloc_size);
    ret->illegal_callback = default_illegal_callback;
    ret->error_callback = default_error_callback;

    if (EXPECT((flags & SECP256K1_FLAGS_TYPE_MASK) != SECP256K1_FLAGS_TYPE_CONTEXT, 0)) {
            secp256k1_callback_call(&ret->illegal_callback,
                                    "Invalid flags");
            return NULL;
    }

    secp256k1_ecmult_context_init(&ret->ecmult_ctx);
    secp256k1_ecmult_gen_context_init(&ret->ecmult_gen_ctx);

    if (flags & SECP256K1_FLAGS_BIT_CONTEXT_SIGN) {
        secp256k1_ecmult_gen_context_build(&ret->ecmult_gen_ctx, &prealloc);
    }
    if (flags & SECP256K1_FLAGS_BIT_CONTEXT_VERIFY) {
        secp256k1_ecmult_context_build(&ret->ecmult_ctx, &prealloc);
    }

    return (secp256k1_context*) ret;
}