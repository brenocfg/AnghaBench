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
typedef  int uint8_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  ptls_minicrypto_log_ctx_t ;

/* Variables and functions */
 int PTLS_ERROR_BER_MALFORMED_TYPE ; 
 size_t ptls_asn1_error_message (char*,size_t,size_t,int,int /*<<< orphan*/ *) ; 

size_t ptls_asn1_read_type(const uint8_t *bytes, size_t bytes_max, int *structure_bit, int *type_class, uint32_t *type_number,
                           int *decode_error, int level, ptls_minicrypto_log_ctx_t *log_ctx)
{
    /* Get the type byte */
    size_t byte_index = 1;
    uint8_t first_byte = bytes[0];
    *structure_bit = (first_byte >> 5) & 1;
    *type_class = (first_byte >> 6) & 3;
    *type_number = first_byte & 31;

    if (*type_number == 31) {
        uint32_t long_type = 0;
        const uint32_t type_number_limit = 0x07FFFFFFF;
        int next_byte;
        int end_found = 0;

        while (byte_index < bytes_max && long_type <= type_number_limit) {
            next_byte = bytes[byte_index++];
            long_type <<= 7;
            long_type |= next_byte & 127;
            if ((next_byte & 128) == 0) {
                end_found = 1;
                break;
            }
        }

        if (end_found) {
            *type_number = long_type;
        } else {
            /* This is an error */
            byte_index = ptls_asn1_error_message("Incorrect type coding", bytes_max, byte_index, level, log_ctx);
            *decode_error = PTLS_ERROR_BER_MALFORMED_TYPE;
        }
    }

    return byte_index;
}