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
struct TYPE_3__ {int /*<<< orphan*/  ctx; int /*<<< orphan*/  (* fn ) (int /*<<< orphan*/ ,char*) ;} ;
typedef  TYPE_1__ ptls_minicrypto_log_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void ptls_asn1_print_indent(int level, ptls_minicrypto_log_ctx_t *log_ctx)
{
    for (int indent = 0; indent <= level; indent++) {
        log_ctx->fn(log_ctx->ctx, "   ");
    }
}