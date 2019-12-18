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
typedef  int /*<<< orphan*/  ldns_status ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_STATUS_DDD_OVERFLOW ; 
 int /*<<< orphan*/  LDNS_STATUS_EMPTY_LABEL ; 
 int /*<<< orphan*/  LDNS_STATUS_OK ; 

ldns_status
ldns_octet(char *word, size_t *length)
{
    char *s; 
    char *p;
    *length = 0;

    for (s = p = word; *s != '\0'; s++,p++) {
        switch (*s) {
            case '.':
                if (s[1] == '.') {
		    return LDNS_STATUS_EMPTY_LABEL;
                }
                *p = *s;
                (*length)++;
                break;
            case '\\':
                if ('0' <= s[1] && s[1] <= '9' &&
                    '0' <= s[2] && s[2] <= '9' &&
                    '0' <= s[3] && s[3] <= '9') {
                    /* \DDD seen */
                    int val = ((s[1] - '0') * 100 +
                           (s[2] - '0') * 10 + (s[3] - '0'));

                    if (0 <= val && val <= 255) {
                        /* this also handles \0 */
                        s += 3;
                        *p = val;
                        (*length)++;
                    } else {
                        return LDNS_STATUS_DDD_OVERFLOW;
                    }
                } else {
                    /* an espaced character, like \<space> ? 
                    * remove the '\' keep the rest */
                    *p = *++s;
                    (*length)++;
                }
                break;
            case '\"':
                /* non quoted " Is either first or the last character in
                 * the string */

                *p = *++s; /* skip it */
                (*length)++;
		/* I'm not sure if this is needed in libdns... MG */
                if ( *s == '\0' ) {
                    /* ok, it was the last one */
                    *p  = '\0'; 
		    return LDNS_STATUS_OK;
                }
                break;
            default:
                *p = *s;
                (*length)++;
                break;
        }
    }
    *p = '\0';
    return LDNS_STATUS_OK;
}