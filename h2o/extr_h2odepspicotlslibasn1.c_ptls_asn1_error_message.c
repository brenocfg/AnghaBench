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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_4__ {int /*<<< orphan*/  ctx; int /*<<< orphan*/  (* fn ) (int /*<<< orphan*/ ,char*,char const*,int,int /*<<< orphan*/ ,int) ;} ;
typedef  TYPE_1__ ptls_minicrypto_log_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  ptls_asn1_print_indent (int,TYPE_1__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*,char const*,int,int /*<<< orphan*/ ,int) ; 

size_t ptls_asn1_error_message(char const *error_label, size_t bytes_max, size_t byte_index, int level,
                               ptls_minicrypto_log_ctx_t *log_ctx)
{
    if (log_ctx != NULL) {
        ptls_asn1_print_indent(level, log_ctx);
        log_ctx->fn(log_ctx->ctx, "Error: %s (near position: %d (0x%x) out of %d)", error_label, (int)byte_index,
                    (uint32_t)byte_index, (int)bytes_max);
    }
    return byte_index;
}