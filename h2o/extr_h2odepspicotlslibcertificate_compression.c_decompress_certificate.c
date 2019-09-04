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
typedef  scalar_t__ uint16_t ;
typedef  int /*<<< orphan*/  ptls_t ;
struct TYPE_4__ {size_t len; int /*<<< orphan*/  base; } ;
typedef  TYPE_1__ ptls_iovec_t ;
typedef  int /*<<< orphan*/  ptls_decompress_certificate_t ;

/* Variables and functions */
 scalar_t__ BROTLI_DECODER_RESULT_SUCCESS ; 
 scalar_t__ BrotliDecoderDecompress (size_t,int /*<<< orphan*/ ,size_t*,int /*<<< orphan*/ ) ; 
 int PTLS_ALERT_BAD_CERTIFICATE ; 
 scalar_t__ PTLS_CERTIFICATE_COMPRESSION_ALGORITHM_BROTLI ; 

__attribute__((used)) static inline int decompress_certificate(ptls_decompress_certificate_t *self, ptls_t *tls, uint16_t algorithm, ptls_iovec_t output,
                                         ptls_iovec_t input)
{
    if (algorithm != PTLS_CERTIFICATE_COMPRESSION_ALGORITHM_BROTLI)
        goto Fail;

    size_t decoded_size = output.len;
    if (BrotliDecoderDecompress(input.len, input.base, &decoded_size, output.base) != BROTLI_DECODER_RESULT_SUCCESS)
        goto Fail;

    if (decoded_size != output.len)
        goto Fail;

    return 0;
Fail:
    return PTLS_ALERT_BAD_CERTIFICATE;
}