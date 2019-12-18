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
typedef  int /*<<< orphan*/  xcb_char2b_t ;
typedef  scalar_t__ iconv_t ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*) ; 
 size_t iconv (scalar_t__,char**,size_t*,char**,size_t*) ; 
 scalar_t__ iconv_open (char*,char*) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/ * smalloc (size_t) ; 
 int /*<<< orphan*/ * srealloc (int /*<<< orphan*/ *,size_t) ; 
 size_t strlen (char*) ; 
 scalar_t__ ucs2_conversion_descriptor ; 

xcb_char2b_t *convert_utf8_to_ucs2(char *input, size_t *real_strlen) {
    /* Calculate the input buffer size (UTF-8 is strlen-safe) */
    size_t input_size = strlen(input);

    /* Calculate the output buffer size and allocate the buffer */
    size_t buffer_size = input_size * sizeof(xcb_char2b_t);
    xcb_char2b_t *buffer = smalloc(buffer_size);

    /* We need to use an additional pointer, because iconv() modifies it */
    size_t output_bytes_left = buffer_size;
    xcb_char2b_t *output = buffer;

    if (ucs2_conversion_descriptor == (iconv_t)-1) {
        /* Get a new conversion descriptor. //IGNORE is a GNU suffix that makes
         * iconv to silently discard characters that cannot be represented in
         * the target character set. */
        ucs2_conversion_descriptor = iconv_open("UCS-2BE//IGNORE", "UTF-8");
        if (ucs2_conversion_descriptor == (iconv_t)-1) {
            ucs2_conversion_descriptor = iconv_open("UCS-2BE", "UTF-8");
        }
        if (ucs2_conversion_descriptor == (iconv_t)-1) {
            err(EXIT_FAILURE, "Error opening the conversion context");
        }
    } else {
        /* Reset the existing conversion descriptor */
        iconv(ucs2_conversion_descriptor, NULL, NULL, NULL, NULL);
    }

    /* Do the conversion */
    size_t rc = iconv(ucs2_conversion_descriptor, &input, &input_size,
                      (char **)&output, &output_bytes_left);
    if (rc == (size_t)-1) {
        /* Conversion will only be partial. */
        perror("Converting to UCS-2 failed");
    }

    /* If no bytes where converted, this is equivalent to freeing buffer. */
    buffer_size -= output_bytes_left;
    buffer = srealloc(buffer, buffer_size);

    /* Return the resulting string's length */
    if (real_strlen != NULL) {
        *real_strlen = buffer_size / sizeof(xcb_char2b_t);
    }

    return buffer;
}