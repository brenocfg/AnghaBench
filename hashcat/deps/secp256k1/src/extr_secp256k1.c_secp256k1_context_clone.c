#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  error_callback; } ;
typedef  TYPE_1__ secp256k1_context ;

/* Variables and functions */
 int /*<<< orphan*/  VERIFY_CHECK (int /*<<< orphan*/ ) ; 
 scalar_t__ checked_malloc (int /*<<< orphan*/ *,size_t) ; 
 TYPE_1__* secp256k1_context_preallocated_clone (TYPE_1__ const*,TYPE_1__*) ; 
 size_t secp256k1_context_preallocated_clone_size (TYPE_1__ const*) ; 

secp256k1_context* secp256k1_context_clone(const secp256k1_context* ctx) {
    secp256k1_context* ret;
    size_t prealloc_size;

    VERIFY_CHECK(ctx != NULL);
    prealloc_size = secp256k1_context_preallocated_clone_size(ctx);
    ret = (secp256k1_context*)checked_malloc(&ctx->error_callback, prealloc_size);
    ret = secp256k1_context_preallocated_clone(ctx, ret);
    return ret;
}