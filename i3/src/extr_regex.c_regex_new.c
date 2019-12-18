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
struct regex {int /*<<< orphan*/  regex; int /*<<< orphan*/  extra; int /*<<< orphan*/  pattern; } ;

/* Variables and functions */
 int /*<<< orphan*/  ELOG (char*,...) ; 
 int PCRE_UCP ; 
 int PCRE_UTF8 ; 
 int /*<<< orphan*/  pcre_compile2 (char const*,int,int*,char const**,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pcre_study (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const**) ; 
 int /*<<< orphan*/  regex_free (struct regex*) ; 
 struct regex* scalloc (int,int) ; 
 int /*<<< orphan*/  sstrdup (char const*) ; 

struct regex *regex_new(const char *pattern) {
    const char *error;
    int errorcode, offset;

    struct regex *re = scalloc(1, sizeof(struct regex));
    re->pattern = sstrdup(pattern);
    int options = PCRE_UTF8;
    /* We use PCRE_UCP so that \B, \b, \D, \d, \S, \s, \W, \w and some POSIX
     * character classes play nicely with Unicode */
    options |= PCRE_UCP;
    while (!(re->regex = pcre_compile2(pattern, options, &errorcode, &error, &offset, NULL))) {
        /* If the error is that PCRE was not compiled with UTF-8 support we
         * disable it and try again */
        if (errorcode == 32) {
            options &= ~PCRE_UTF8;
            continue;
        }
        ELOG("PCRE regular expression compilation failed at %d: %s\n",
             offset, error);
        regex_free(re);
        return NULL;
    }
    re->extra = pcre_study(re->regex, 0, &error);
    /* If an error happened, we print the error message, but continue.
     * Studying the regular expression leads to faster matching, but it’s not
     * absolutely necessary. */
    if (error) {
        ELOG("PCRE regular expression studying failed: %s\n", error);
    }
    return re;
}