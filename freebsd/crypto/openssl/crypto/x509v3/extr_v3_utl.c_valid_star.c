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
 int LABEL_HYPHEN ; 
 int LABEL_IDNA ; 
 int LABEL_START ; 
 unsigned int X509_CHECK_FLAG_NO_PARTIAL_WILDCARDS ; 
 scalar_t__ strncasecmp (char*,char*,int) ; 

__attribute__((used)) static const unsigned char *valid_star(const unsigned char *p, size_t len,
                                       unsigned int flags)
{
    const unsigned char *star = 0;
    size_t i;
    int state = LABEL_START;
    int dots = 0;
    for (i = 0; i < len; ++i) {
        /*
         * Locate first and only legal wildcard, either at the start
         * or end of a non-IDNA first and not final label.
         */
        if (p[i] == '*') {
            int atstart = (state & LABEL_START);
            int atend = (i == len - 1 || p[i + 1] == '.');
            /*-
             * At most one wildcard per pattern.
             * No wildcards in IDNA labels.
             * No wildcards after the first label.
             */
            if (star != NULL || (state & LABEL_IDNA) != 0 || dots)
                return NULL;
            /* Only full-label '*.example.com' wildcards? */
            if ((flags & X509_CHECK_FLAG_NO_PARTIAL_WILDCARDS)
                && (!atstart || !atend))
                return NULL;
            /* No 'foo*bar' wildcards */
            if (!atstart && !atend)
                return NULL;
            star = &p[i];
            state &= ~LABEL_START;
        } else if (('a' <= p[i] && p[i] <= 'z')
                   || ('A' <= p[i] && p[i] <= 'Z')
                   || ('0' <= p[i] && p[i] <= '9')) {
            if ((state & LABEL_START) != 0
                && len - i >= 4 && strncasecmp((char *)&p[i], "xn--", 4) == 0)
                state |= LABEL_IDNA;
            state &= ~(LABEL_HYPHEN | LABEL_START);
        } else if (p[i] == '.') {
            if ((state & (LABEL_HYPHEN | LABEL_START)) != 0)
                return NULL;
            state = LABEL_START;
            ++dots;
        } else if (p[i] == '-') {
            /* no domain/subdomain starts with '-' */
            if ((state & LABEL_START) != 0)
                return NULL;
            state |= LABEL_HYPHEN;
        } else
            return NULL;
    }

    /*
     * The final label must not end in a hyphen or ".", and
     * there must be at least two dots after the star.
     */
    if ((state & (LABEL_START | LABEL_HYPHEN)) != 0 || dots < 2)
        return NULL;
    return star;
}