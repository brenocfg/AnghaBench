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
struct regex {int /*<<< orphan*/  pattern; int /*<<< orphan*/  extra; int /*<<< orphan*/  regex; } ;

/* Variables and functions */
 int /*<<< orphan*/  ELOG (char*,int,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  LOG (char*,int /*<<< orphan*/ ,char const*) ; 
 int PCRE_ERROR_NOMATCH ; 
 int pcre_exec (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

bool regex_matches(struct regex *regex, const char *input) {
    int rc;

    /* We use strlen() because pcre_exec() expects the length of the input
     * string in bytes */
    if ((rc = pcre_exec(regex->regex, regex->extra, input, strlen(input), 0, 0, NULL, 0)) == 0) {
        LOG("Regular expression \"%s\" matches \"%s\"\n",
            regex->pattern, input);
        return true;
    }

    if (rc == PCRE_ERROR_NOMATCH) {
        LOG("Regular expression \"%s\" does not match \"%s\"\n",
            regex->pattern, input);
        return false;
    }

    ELOG("PCRE error %d while trying to use regular expression \"%s\" on input \"%s\", see pcreapi(3)\n",
         rc, regex->pattern, input);
    return false;
}