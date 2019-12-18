#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {size_t fnm_len; int /*<<< orphan*/  fnm_name; } ;
typedef  TYPE_1__ ao_flag_names_t ;

/* Variables and functions */
 int AOUF_COUNT ; 
 int /*<<< orphan*/  IS_END_LIST_ENTRY_CHAR (char const) ; 
#define  NUL 128 
 char* SPN_WHITESPACE_CHARS (char const*) ; 
 char* getenv (char*) ; 
 scalar_t__ strneqvcmp (char const*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static unsigned int
parse_usage_flags(ao_flag_names_t const * fnt, char const * txt)
{
    unsigned int res = 0;

    /*
     * The text may be passed in.  If not, use the environment variable.
     */
    if (txt == NULL) {
        txt = getenv("AUTOOPTS_USAGE");
        if (txt == NULL)
            return 0;
    }

    txt = SPN_WHITESPACE_CHARS(txt);
    if (*txt == NUL)
        return 0;

    /*
     * search the string for table entries.  We must understand everything
     * we see in the string, or we give up on it.
     */
    for (;;) {
        int ix = 0;

        for (;;) {
            if (strneqvcmp(txt, fnt[ix].fnm_name, (int)fnt[ix].fnm_len) == 0)
                break;
            if (++ix >= AOUF_COUNT)
                return 0;
        }

        /*
         *  Make sure we have a full match.  Look for whitespace,
         *  a comma, or a NUL byte.
         */
        if (! IS_END_LIST_ENTRY_CHAR(txt[fnt[ix].fnm_len]))
            return 0;

        res |= 1U << ix;
        txt = SPN_WHITESPACE_CHARS(txt + fnt[ix].fnm_len);

        switch (*txt) {
        case NUL:
            return res;

        case ',':
            txt = SPN_WHITESPACE_CHARS(txt + 1);
            /* Something must follow the comma */

        default:
            continue;
        }
    }
}