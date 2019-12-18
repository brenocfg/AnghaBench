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
 unsigned int X509_CHECK_FLAG_SINGLE_LABEL_SUBDOMAINS ; 
 unsigned int _X509_CHECK_FLAG_DOT_SUBDOMAINS ; 

__attribute__((used)) static void skip_prefix(const unsigned char **p, size_t *plen,
                        size_t subject_len,
                        unsigned int flags)
{
    const unsigned char *pattern = *p;
    size_t pattern_len = *plen;

    /*
     * If subject starts with a leading '.' followed by more octets, and
     * pattern is longer, compare just an equal-length suffix with the
     * full subject (starting at the '.'), provided the prefix contains
     * no NULs.
     */
    if ((flags & _X509_CHECK_FLAG_DOT_SUBDOMAINS) == 0)
        return;

    while (pattern_len > subject_len && *pattern) {
        if ((flags & X509_CHECK_FLAG_SINGLE_LABEL_SUBDOMAINS) &&
            *pattern == '.')
            break;
        ++pattern;
        --pattern_len;
    }

    /* Skip if entire prefix acceptable */
    if (pattern_len == subject_len) {
        *p = pattern;
        *plen = pattern_len;
    }
}