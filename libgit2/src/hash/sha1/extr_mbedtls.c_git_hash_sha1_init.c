#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  c; } ;
typedef  TYPE_1__ git_hash_sha1_ctx ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  mbedtls_sha1_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_sha1_starts (int /*<<< orphan*/ *) ; 

int git_hash_sha1_init(git_hash_sha1_ctx *ctx)
{
    assert(ctx);
    mbedtls_sha1_init(&ctx->c);
    mbedtls_sha1_starts(&ctx->c);
    return 0;
}