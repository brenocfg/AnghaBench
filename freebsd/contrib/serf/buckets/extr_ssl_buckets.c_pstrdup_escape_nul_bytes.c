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
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 char* apr_palloc (int /*<<< orphan*/ *,int) ; 
 char* apr_pstrdup (int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static char *
pstrdup_escape_nul_bytes(const char *buf, int len, apr_pool_t *pool)
{
    int i, nul_count = 0;
    char *ret;

    /* First determine if there are any nul bytes in the string. */
    for (i = 0; i < len; i++) {
        if (buf[i] == '\0')
            nul_count++;
    }

    if (nul_count == 0) {
        /* There aren't so easy case to just copy the string */
        ret = apr_pstrdup(pool, buf);
    } else {
        /* There are so we have to replace nul bytes with escape codes
         * Proper length is the length of the original string, plus
         * 2 times the number of nulls (for two digit hex code for
         * the value) + the trailing null. */
        char *pos;
        ret = pos = apr_palloc(pool, len + 2 * nul_count + 1);
        for (i = 0; i < len; i++) {
            if (buf[i] != '\0') {
                *(pos++) = buf[i];
            } else {
                *(pos++) = '\\';
                *(pos++) = '0';
                *(pos++) = '0';
            }
        }
        *pos = '\0';
    }

    return ret;
}