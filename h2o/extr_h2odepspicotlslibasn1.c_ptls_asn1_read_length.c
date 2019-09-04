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
 int PTLS_ERROR_BER_EXCESSIVE_LENGTH ; 
 int PTLS_ERROR_BER_MALFORMED_LENGTH ; 
 size_t ptls_asn1_error_message (char*,size_t,size_t,int,int /*<<< orphan*/ *) ; 

size_t ptls_asn1_read_length(const uint8_t *bytes, size_t bytes_max, size_t byte_index, uint32_t *length, int *indefinite_length,
                             size_t *last_byte, int *decode_error, int level, ptls_minicrypto_log_ctx_t *log_ctx)
{
    int length_of_length = 0;

    *indefinite_length = 0;
    *length = 0;
    *last_byte = bytes_max;

    if (byte_index < bytes_max) {
        *length = bytes[byte_index++];
        if ((*length & 128) != 0) {
            length_of_length = *length & 127;
            *length = 0;

            if (byte_index + length_of_length >= bytes_max) {
                /* This is an error */
                byte_index = ptls_asn1_error_message("Incorrect length coding", bytes_max, byte_index, level, log_ctx);
                *decode_error = PTLS_ERROR_BER_MALFORMED_LENGTH;
            } else {
                for (int i = 0; i < length_of_length && byte_index < bytes_max; i++) {
                    *length <<= 8;
                    *length |= bytes[byte_index++];
                }

                if (length_of_length == 0) {
                    *last_byte = bytes_max;
                    *indefinite_length = 1;
                } else {
                    *last_byte = byte_index + *length;
                }
            }
        } else {
            *last_byte = byte_index + *length;
        }

        if (*decode_error == 0) {
            /* TODO: verify that the length makes sense */
            if (*last_byte > bytes_max) {
                byte_index = ptls_asn1_error_message("Length larger than message", bytes_max, byte_index, level, log_ctx);
                *decode_error = PTLS_ERROR_BER_EXCESSIVE_LENGTH;
            }
        }
    }

    return byte_index;
}