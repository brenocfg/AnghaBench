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
typedef  int /*<<< orphan*/  secp256k1_scratch_space ;
struct TYPE_3__ {int /*<<< orphan*/  error_callback; } ;
typedef  TYPE_1__ secp256k1_context ;

/* Variables and functions */
 int /*<<< orphan*/  VERIFY_CHECK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  secp256k1_scratch_destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void secp256k1_scratch_space_destroy(const secp256k1_context *ctx, secp256k1_scratch_space* scratch) {
    VERIFY_CHECK(ctx != NULL);
    secp256k1_scratch_destroy(&ctx->error_callback, scratch);
}