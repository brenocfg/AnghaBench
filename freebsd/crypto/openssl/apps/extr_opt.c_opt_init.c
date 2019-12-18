#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {char* name; int valtype; scalar_t__ retval; } ;
typedef  TYPE_1__ OPTIONS ;

/* Variables and functions */
 char* OPT_HELP_STR ; 
 char* OPT_MORE_STR ; 
 int argc ; 
 char** argv ; 
 int /*<<< orphan*/  assert (int) ; 
 int opt_index ; 
 int /*<<< orphan*/  opt_progname (char*) ; 
 TYPE_1__ const* opts ; 
 char* prog ; 
 scalar_t__ strcmp (char*,char*) ; 
 TYPE_1__ const* unknown ; 

char *opt_init(int ac, char **av, const OPTIONS *o)
{
    /* Store state. */
    argc = ac;
    argv = av;
    opt_index = 1;
    opts = o;
    opt_progname(av[0]);
    unknown = NULL;

    for (; o->name; ++o) {
#ifndef NDEBUG
        const OPTIONS *next;
        int duplicated, i;
#endif

        if (o->name == OPT_HELP_STR || o->name == OPT_MORE_STR)
            continue;
#ifndef NDEBUG
        i = o->valtype;

        /* Make sure options are legit. */
        assert(o->name[0] != '-');
        assert(o->retval > 0);
        switch (i) {
        case   0: case '-': case '/': case '<': case '>': case 'E': case 'F':
        case 'M': case 'U': case 'f': case 'l': case 'n': case 'p': case 's':
        case 'u': case 'c':
            break;
        default:
            assert(0);
        }

        /* Make sure there are no duplicates. */
        for (next = o + 1; next->name; ++next) {
            /*
             * Some compilers inline strcmp and the assert string is too long.
             */
            duplicated = strcmp(o->name, next->name) == 0;
            assert(!duplicated);
        }
#endif
        if (o->name[0] == '\0') {
            assert(unknown == NULL);
            unknown = o;
            assert(unknown->valtype == 0 || unknown->valtype == '-');
        }
    }
    return prog;
}