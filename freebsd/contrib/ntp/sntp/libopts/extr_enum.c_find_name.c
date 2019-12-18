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
typedef  int /*<<< orphan*/  tOptions ;
typedef  int /*<<< orphan*/  tOptDesc ;

/* Variables and functions */
 scalar_t__ IS_DEC_DIGIT_CHAR (char const) ; 
 scalar_t__ IS_INVERSION_CHAR (char const) ; 
 char NUL ; 
 int /*<<< orphan*/  enum_err (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const* const*,int) ; 
 int /*<<< orphan*/  option_usage_fp ; 
 int /*<<< orphan*/  pz_enum_err_fmt ; 
 int /*<<< orphan*/  stderr ; 
 size_t strlen (char const*) ; 
 scalar_t__ strncmp (char const* const,char const*,size_t) ; 
 unsigned long strtoul (char const*,char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zNoKey ; 
 int /*<<< orphan*/  zambiguous_key ; 
 int /*<<< orphan*/  znum_too_large ; 

__attribute__((used)) static uintptr_t
find_name(char const * name, tOptions * pOpts, tOptDesc * pOD,
          char const * const *  paz_names, unsigned int name_ct)
{
    /*
     *  Return the matching index as a pointer sized integer.
     *  The result gets stashed in a char * pointer.
     */
    uintptr_t   res = name_ct;
    size_t      len = strlen(name);
    uintptr_t   idx;

    if (IS_DEC_DIGIT_CHAR(*name)) {
        char * pz;
        unsigned long val = strtoul(name, &pz, 0);
        if ((*pz == NUL) && (val < name_ct))
            return (uintptr_t)val;
        pz_enum_err_fmt = znum_too_large;
        option_usage_fp = stderr;
        enum_err(pOpts, pOD, paz_names, (int)name_ct);
        return name_ct;
    }

    if (IS_INVERSION_CHAR(*name) && (name[2] == NUL)) {
        if (  ((name[0] == '~') && (name[1] == '0'))
           || ((name[0] == '-') && (name[1] == '1')))
        return (uintptr_t)(name_ct - 1);
        goto oops;
    }

    /*
     *  Look for an exact match, but remember any partial matches.
     *  Multiple partial matches means we have an ambiguous match.
     */
    for (idx = 0; idx < name_ct; idx++) {
        if (strncmp(paz_names[idx], name, len) == 0) {
            if (paz_names[idx][len] == NUL)
                return idx;  /* full match */

            if (res == name_ct)
                res = idx; /* save partial match */
            else
                res = (uintptr_t)~0;  /* may yet find full match */
        }
    }

    if (res < name_ct)
        return res; /* partial match */

 oops:

    pz_enum_err_fmt = (res == name_ct) ? zNoKey : zambiguous_key;
    option_usage_fp = stderr;
    enum_err(pOpts, pOD, paz_names, (int)name_ct);
    return name_ct;
}