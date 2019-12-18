#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char const* argString; } ;
struct TYPE_5__ {TYPE_1__ optArg; int /*<<< orphan*/  optCookie; } ;
typedef  TYPE_2__ tOptDesc ;

/* Variables and functions */
 char const NUL ; 
 char* SPN_WHITESPACE_CHARS (char const*) ; 

__attribute__((used)) static uintptr_t
check_membership_start(tOptDesc * od, char const ** argp, bool * invert)
{
    uintptr_t    res = (uintptr_t)od->optCookie;
    char const * arg = SPN_WHITESPACE_CHARS(od->optArg.argString);
    if ((arg == NULL) || (*arg == NUL))
        goto member_start_fail;

    *invert = false;

    switch (*arg) {
    case '=':
        res = 0UL;
        arg = SPN_WHITESPACE_CHARS(arg + 1);
        switch (*arg) {
        case '=': case ',':
            goto member_start_fail;
        case '^':
            goto inversion;
        default:
            break;
        }
        break;

    case '^':
    inversion:
        *invert = true;
        arg = SPN_WHITESPACE_CHARS(arg + 1);
        if (*arg != ',')
            break;
        /* FALLTHROUGH */

    case ',':
        goto member_start_fail;

    default:
        break;
    }

    *argp = arg;
    return res;

member_start_fail:
    *argp = NULL;
    return 0UL;
}