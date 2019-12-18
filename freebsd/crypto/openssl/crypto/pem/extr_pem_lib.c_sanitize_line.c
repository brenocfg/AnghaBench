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
 unsigned int PEM_FLAG_EAY_COMPATIBLE ; 
 unsigned int PEM_FLAG_ONLY_B64 ; 
 int /*<<< orphan*/  ossl_isbase64 (char) ; 
 scalar_t__ ossl_iscntrl (char) ; 

__attribute__((used)) static int sanitize_line(char *linebuf, int len, unsigned int flags)
{
    int i;

    if (flags & PEM_FLAG_EAY_COMPATIBLE) {
        /* Strip trailing whitespace */
        while ((len >= 0) && (linebuf[len] <= ' '))
            len--;
        /* Go back to whitespace before applying uniform line ending. */
        len++;
    } else if (flags & PEM_FLAG_ONLY_B64) {
        for (i = 0; i < len; ++i) {
            if (!ossl_isbase64(linebuf[i]) || linebuf[i] == '\n'
                || linebuf[i] == '\r')
                break;
        }
        len = i;
    } else {
        /* EVP_DecodeBlock strips leading and trailing whitespace, so just strip
         * control characters in-place and let everything through. */
        for (i = 0; i < len; ++i) {
            if (linebuf[i] == '\n' || linebuf[i] == '\r')
                break;
            if (ossl_iscntrl(linebuf[i]))
                linebuf[i] = ' ';
        }
        len = i;
    }
    /* The caller allocated LINESIZE+1, so this is safe. */
    linebuf[len++] = '\n';
    linebuf[len] = '\0';
    return len;
}