#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_9__ {int /*<<< orphan*/  ctx; int /*<<< orphan*/  (* fn ) (int /*<<< orphan*/ ,char*) ;} ;
typedef  TYPE_1__ ptls_minicrypto_log_ctx_t ;

/* Variables and functions */
 int PTLS_ERROR_BER_UNEXPECTED_EOC ; 
 int /*<<< orphan*/  ptls_asn1_dump_content (scalar_t__ const*,size_t,size_t,TYPE_1__*) ; 
 size_t ptls_asn1_error_message (char*,size_t,size_t,int,TYPE_1__*) ; 
 int /*<<< orphan*/  ptls_asn1_print_indent (int,TYPE_1__*) ; 
 int /*<<< orphan*/  ptls_asn1_print_type (int,int /*<<< orphan*/ ,int,TYPE_1__*) ; 
 size_t ptls_asn1_read_length (scalar_t__ const*,size_t,size_t,int /*<<< orphan*/ *,int*,size_t*,int*,int,TYPE_1__*) ; 
 size_t ptls_asn1_read_type (scalar_t__ const*,size_t,int*,int*,int /*<<< orphan*/ *,int*,int,TYPE_1__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub5 (int /*<<< orphan*/ ,char*) ; 

size_t ptls_asn1_validation_recursive(const uint8_t *bytes, size_t bytes_max, int *decode_error, int level,
                                      ptls_minicrypto_log_ctx_t *log_ctx)
{
    /* Get the type byte */
    int structure_bit = 0;
    int type_class = 0;
    uint32_t type_number = 0;
    uint32_t length = 0;
    int indefinite_length = 0;
    size_t last_byte = 0;
    /* Decode the type */
    size_t byte_index =
        ptls_asn1_read_type(bytes, bytes_max, &structure_bit, &type_class, &type_number, decode_error, level, log_ctx);

    if (*decode_error == 0 && log_ctx != NULL) {
        ptls_asn1_print_type(type_class, type_number, level, log_ctx);
    }

    /* Get the length */
    byte_index =
        ptls_asn1_read_length(bytes, bytes_max, byte_index, &length, &indefinite_length, &last_byte, decode_error, level, log_ctx);

    if (last_byte <= bytes_max) {
        if (structure_bit) {
            /* If structured, recurse on a loop */
            if (log_ctx != NULL) {
                log_ctx->fn(log_ctx->ctx, " {\n");
            }

            while (byte_index < last_byte) {
                if (indefinite_length != 0 && bytes[byte_index] == 0) {
                    if (byte_index + 2 > bytes_max || bytes[byte_index + 1] != 0) {
                        byte_index =
                            ptls_asn1_error_message("EOC: unexpected end of content", bytes_max, byte_index, level + 1, log_ctx);

                        *decode_error = PTLS_ERROR_BER_UNEXPECTED_EOC;
                        byte_index = bytes_max;
                        break;
                    } else {
                        if (log_ctx != NULL) {
                            ptls_asn1_print_indent(level, log_ctx);
                            log_ctx->fn(log_ctx->ctx, "EOC\n");
                        }
                        byte_index += 2;
                        break;
                    }
                } else {
                    byte_index += ptls_asn1_validation_recursive(bytes + byte_index, last_byte - byte_index, decode_error,
                                                                 level + 1, log_ctx);

                    if (*decode_error) {
                        byte_index = bytes_max;
                        break;
                    }
                }

                if (log_ctx != NULL) {
                    if (byte_index < last_byte) {
                        log_ctx->fn(log_ctx->ctx, ",");
                    }
                    log_ctx->fn(log_ctx->ctx, "\n");
                }
            }

            if (log_ctx != NULL) {
                ptls_asn1_print_indent(level, log_ctx);
                log_ctx->fn(log_ctx->ctx, "}");
            }
        } else {
            ptls_asn1_dump_content(bytes, last_byte, byte_index, log_ctx);
            byte_index = last_byte;
        }
    }

    return byte_index;
}