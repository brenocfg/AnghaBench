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

/* Variables and functions */
 int H2O_HTTP2_ERROR_INVALID_HEADER_CHAR ; 
 int H2O_HTTP3_ERROR_QPACK_DECOMPRESSION_FAILED ; 

__attribute__((used)) static int normalize_error_code(int err)
{
    /* convert H2 errors (except invaild_header_char) to QPACK error code */
    if (err < 0 && err != H2O_HTTP2_ERROR_INVALID_HEADER_CHAR)
        err = H2O_HTTP3_ERROR_QPACK_DECOMPRESSION_FAILED;
    return err;
}