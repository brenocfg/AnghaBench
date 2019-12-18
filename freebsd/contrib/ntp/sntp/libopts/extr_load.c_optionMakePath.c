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
#define  NUL 128 
 int /*<<< orphan*/  add_env_val (char*,int,char const*) ; 
 int /*<<< orphan*/  add_prog_path (char*,int,char const*,char const*) ; 
 int get_realpath (char*,int) ; 
 int const* program_pkgdatadir ; 
 int snprintf (char*,size_t,char*,int const*,char const*) ; 
 size_t strlen (char const*) ; 

bool
optionMakePath(char * p_buf, int b_sz, char const * fname, char const * prg_path)
{
    {
        size_t len = strlen(fname);

        if (((size_t)b_sz <= len) || (len == 0))
            return false;
    }

    /*
     *  IF not an environment variable, just copy the data
     */
    if (*fname != '$') {
        char   const * src = fname;
        char * dst = p_buf;
        int    ct  = b_sz;

        for (;;) {
            if ( (*(dst++) = *(src++)) == NUL)
                break;
            if (--ct <= 0)
                return false;
        }
    }

    /*
     *  IF the name starts with "$$", then it must be "$$" or
     *  it must start with "$$/".  In either event, replace the "$$"
     *  with the path to the executable and append a "/" character.
     */
    else switch (fname[1]) {
    case NUL:
        return false;

    case '$':
        if (! add_prog_path(p_buf, b_sz, fname, prg_path))
            return false;
        break;

    case '@':
        if (program_pkgdatadir[0] == NUL)
            return false;

        if (snprintf(p_buf, (size_t)b_sz, "%s%s",
                     program_pkgdatadir, fname + 2) >= b_sz)
            return false;
        break;

    default:
        if (! add_env_val(p_buf, b_sz, fname))
            return false;
    }

    return get_realpath(p_buf, b_sz);
}