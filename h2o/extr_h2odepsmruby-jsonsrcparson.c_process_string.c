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
 int /*<<< orphan*/  JSONFailure ; 
 int /*<<< orphan*/  memcpy (char*,char*,size_t) ; 
 int /*<<< orphan*/  parse_utf16 (char const**,char**) ; 
 int /*<<< orphan*/  parson_free (char*) ; 
 scalar_t__ parson_malloc (size_t) ; 

__attribute__((used)) static char* process_string(const char *input, size_t len) {
    const char *input_ptr = input;
    size_t initial_size = (len + 1) * sizeof(char);
    size_t final_size = 0;
    char *output = NULL, *output_ptr = NULL, *resized_output = NULL;
    output = (char*)parson_malloc(initial_size);
    if (output == NULL) {
        goto error;
    }
    output_ptr = output;
    while ((*input_ptr != '\0') && (size_t)(input_ptr - input) < len) {
        if (*input_ptr == '\\') {
            input_ptr++;
            switch (*input_ptr) {
                case '\"': *output_ptr = '\"'; break;
                case '\\': *output_ptr = '\\'; break;
                case '/':  *output_ptr = '/';  break;
                case 'b':  *output_ptr = '\b'; break;
                case 'f':  *output_ptr = '\f'; break;
                case 'n':  *output_ptr = '\n'; break;
                case 'r':  *output_ptr = '\r'; break;
                case 't':  *output_ptr = '\t'; break;
                case 'u':
                    if (parse_utf16(&input_ptr, &output_ptr) == JSONFailure) {
                        goto error;
                    }
                    break;
                default:
                    goto error;
            }
        } else if ((unsigned char)*input_ptr < 0x20) {
            goto error; /* 0x00-0x19 are invalid characters for json string (http://www.ietf.org/rfc/rfc4627.txt) */
        } else {
            *output_ptr = *input_ptr;
        }
        output_ptr++;
        input_ptr++;
    }
    *output_ptr = '\0';
    /* resize to new length */
    final_size = (size_t)(output_ptr-output) + 1;
    /* todo: don't resize if final_size == initial_size */
    resized_output = (char*)parson_malloc(final_size);
    if (resized_output == NULL) {
        goto error;
    }
    memcpy(resized_output, output, final_size);
    parson_free(output);
    return resized_output;
error:
    parson_free(output);
    return NULL;
}