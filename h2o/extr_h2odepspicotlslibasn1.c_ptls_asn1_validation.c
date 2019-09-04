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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_4__ {int /*<<< orphan*/  ctx; int /*<<< orphan*/  (* fn ) (int /*<<< orphan*/ ,char*,int,int) ;} ;
typedef  TYPE_1__ ptls_minicrypto_log_ctx_t ;

/* Variables and functions */
 int PTLS_ERROR_BER_ELEMENT_TOO_SHORT ; 
 size_t ptls_asn1_validation_recursive (int /*<<< orphan*/  const*,size_t,int*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*,int,int) ; 

int ptls_asn1_validation(const uint8_t *bytes, size_t length, ptls_minicrypto_log_ctx_t *log_ctx)
{
    int decode_error = 0;
    size_t decoded = ptls_asn1_validation_recursive(bytes, length, &decode_error, 0, log_ctx);

    if (decode_error == 0 && decoded < length) {
        decode_error = PTLS_ERROR_BER_ELEMENT_TOO_SHORT;
        if (log_ctx != NULL) {
            log_ctx->fn(log_ctx->ctx, "Type too short, %d bytes only out of %d\n", (int)decoded, (int)length);
        }
    }

    return decode_error;
}