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
 int /*<<< orphan*/  free (char*) ; 
 size_t iconv (scalar_t__,char**,size_t*,char**,size_t*) ; 
 scalar_t__ iconv_open (char*,char*) ; 
 int /*<<< orphan*/  perror (char*) ; 
 char* scalloc (size_t,int) ; 
 scalar_t__ utf8_conversion_descriptor ; 

char *convert_ucs2_to_utf8(xcb_char2b_t *text, size_t num_glyphs) {
    /* Allocate the output buffer (UTF-8 is at most 4 bytes per glyph) */
    size_t buffer_size = num_glyphs * 4 + 1;
    char *buffer = scalloc(buffer_size, 1);

    /* We need to use an additional pointer, because iconv() modifies it */
    char *output = buffer;
    size_t output_size = buffer_size - 1;

    if (utf8_conversion_descriptor == (iconv_t)-1) {
        /* Get a new conversion descriptor */
        utf8_conversion_descriptor = iconv_open("UTF-8", "UCS-2BE");
        if (utf8_conversion_descriptor == (iconv_t)-1)
            err(EXIT_FAILURE, "Error opening the conversion context");
    } else {
        /* Reset the existing conversion descriptor */
        iconv(utf8_conversion_descriptor, NULL, NULL, NULL, NULL);
    }

    /* Do the conversion */
    size_t input_len = num_glyphs * sizeof(xcb_char2b_t);
    size_t rc = iconv(utf8_conversion_descriptor, (char **)&text,
                      &input_len, &output, &output_size);
    if (rc == (size_t)-1) {
        perror("Converting to UTF-8 failed");
        free(buffer);
        return NULL;
    }

    return buffer;
}