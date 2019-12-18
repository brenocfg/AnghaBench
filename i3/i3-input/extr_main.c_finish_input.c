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
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 scalar_t__ concat_strings (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 char* format ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  glyphs_utf8 ; 
 int /*<<< orphan*/  input_position ; 
 int /*<<< orphan*/  ipc_send_message (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 char* scalloc (int,int) ; 
 int /*<<< orphan*/  sockfd ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strncat (char*,char*,int) ; 

__attribute__((used)) static void finish_input(void) {
    char *command = (char *)concat_strings(glyphs_utf8, input_position);

    /* count the occurrences of %s in the string */
    int c;
    int len = strlen(format);
    int cnt = 0;
    for (c = 0; c < (len - 1); c++)
        if (format[c] == '%' && format[c + 1] == 's')
            cnt++;
    printf("occurrences = %d\n", cnt);

    /* allocate space for the output */
    int inputlen = strlen(command);
    char *full = scalloc(strlen(format) - (2 * cnt) /* format without all %s */
                             + (inputlen * cnt)     /* replaced %s */
                             + 1,                   /* trailing NUL */
                         1);
    char *dest = full;
    for (c = 0; c < len; c++) {
        /* if this is not % or it is % but without a following 's',
         * just copy the character */
        if (format[c] != '%' || (c == (len - 1)) || format[c + 1] != 's')
            *(dest++) = format[c];
        else {
            strncat(dest, command, inputlen);
            dest += inputlen;
            /* skip the following 's' of '%s' */
            c++;
        }
    }

    /* prefix the command if a prefix was specified on commandline */
    printf("command = %s\n", full);

    ipc_send_message(sockfd, strlen(full), 0, (uint8_t *)full);

    free(full);

    exit(0);
}