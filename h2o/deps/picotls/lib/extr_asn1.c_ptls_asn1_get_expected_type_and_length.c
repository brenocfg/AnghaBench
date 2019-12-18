#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ const uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  ptls_minicrypto_log_ctx_t ;

/* Variables and functions */
 int PTLS_ERROR_DER_INDEFINITE_LENGTH ; 
 int PTLS_ERROR_INCORRECT_ASN1_SYNTAX ; 
 size_t ptls_asn1_error_message (char*,size_t,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 size_t ptls_asn1_read_length (scalar_t__ const*,size_t,size_t,int /*<<< orphan*/ *,int*,size_t*,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

size_t ptls_asn1_get_expected_type_and_length(const uint8_t *bytes, size_t bytes_max, size_t byte_index, uint8_t expected_type,
                                              uint32_t *length, int *indefinite_length, size_t *last_byte, int *decode_error,
                                              ptls_minicrypto_log_ctx_t *log_ctx)
{
    int is_indefinite = 0;

    /* Check that the expected type is present */
    if (bytes[byte_index] != expected_type) {
        byte_index = ptls_asn1_error_message("Unexpected type", bytes_max, byte_index, 0, log_ctx);
        *decode_error = PTLS_ERROR_INCORRECT_ASN1_SYNTAX;
    } else {
        /* get length of element */
        byte_index++;
        byte_index =
            ptls_asn1_read_length(bytes, bytes_max, byte_index, length, &is_indefinite, last_byte, decode_error, 0, log_ctx);

        if (indefinite_length != NULL) {
            *indefinite_length = is_indefinite;
        } else if (is_indefinite) {
            byte_index = ptls_asn1_error_message("Incorrect length for DER", bytes_max, byte_index, 0, log_ctx);
            *decode_error = PTLS_ERROR_DER_INDEFINITE_LENGTH;
        }
    }

    return byte_index;
}