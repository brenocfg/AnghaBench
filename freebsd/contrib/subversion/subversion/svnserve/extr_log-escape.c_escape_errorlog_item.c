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
typedef  int apr_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  c2x (unsigned char const,char,unsigned char*) ; 
 scalar_t__ svn_ctype_iscntrl (unsigned char const) ; 
 int /*<<< orphan*/  svn_ctype_isprint (unsigned char const) ; 

apr_size_t escape_errorlog_item(char *dest, const char *source,
                                apr_size_t buflen)
{
    unsigned char *d, *ep;
    const unsigned char *s;

    if (!source || !buflen) { /* be safe */
        return 0;
    }

    d = (unsigned char *)dest;
    s = (const unsigned char *)source;
    ep = d + buflen - 1;

    for (; d < ep && *s; ++s) {

        /* httpd-2.2.4/server/util.c has this:
             if (TEST_CHAR(*s, T_ESCAPE_LOGITEM)) {
           which does this same check with a fast lookup table.  Well,
           mostly the same; we don't escape quotes, as that does.
        */
        if (*s && (   !svn_ctype_isprint(*s)
                   || *s == '\\'
                   || svn_ctype_iscntrl(*s))) {
            *d++ = '\\';
            if (d >= ep) {
                --d;
                break;
            }

            switch(*s) {
            case '\b':
                *d++ = 'b';
                break;
            case '\n':
                *d++ = 'n';
                break;
            case '\r':
                *d++ = 'r';
                break;
            case '\t':
                *d++ = 't';
                break;
            case '\v':
                *d++ = 'v';
                break;
            case '\\':
                *d++ = *s;
                break;
            case '"': /* no need for this in error log */
                d[-1] = *s;
                break;
            default:
                if (d >= ep - 2) {
                    ep = --d; /* break the for loop as well */
                    break;
                }
                c2x(*s, 'x', d);
                d += 3;
            }
        }
        else {
            *d++ = *s;
        }
    }
    *d = '\0';

    return (d - (unsigned char *)dest);
}