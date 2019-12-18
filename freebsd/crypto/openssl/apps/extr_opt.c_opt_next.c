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
typedef  int /*<<< orphan*/  ossl_uintmax_t ;
typedef  int /*<<< orphan*/  ossl_intmax_t ;
struct TYPE_5__ {int retval; } ;
struct TYPE_4__ {char* name; char valtype; int retval; } ;
typedef  TYPE_1__ OPTIONS ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  OPT_FMT_ANY ; 
 int /*<<< orphan*/  OPT_FMT_PDE ; 
 int /*<<< orphan*/  OPT_FMT_PDS ; 
 int /*<<< orphan*/  OPT_FMT_PEMDER ; 
 int /*<<< orphan*/  app_isdir (char*) ; 
 char* arg ; 
 char** argv ; 
 int /*<<< orphan*/  bio_err ; 
 char* dunno ; 
 char* flag ; 
 int /*<<< orphan*/  opt_format (char*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  opt_imax (char*,int /*<<< orphan*/ *) ; 
 size_t opt_index ; 
 int /*<<< orphan*/  opt_int (char*,int*) ; 
 int /*<<< orphan*/  opt_long (char*,long*) ; 
 int /*<<< orphan*/  opt_ulong (char*,unsigned long*) ; 
 int /*<<< orphan*/  opt_umax (char*,int /*<<< orphan*/ *) ; 
 TYPE_1__* opts ; 
 int /*<<< orphan*/  prog ; 
 char* strchr (char*,char) ; 
 scalar_t__ strcmp (char*,char*) ; 
 TYPE_2__* unknown ; 

int opt_next(void)
{
    char *p;
    const OPTIONS *o;
    int ival;
    long lval;
    unsigned long ulval;
    ossl_intmax_t imval;
    ossl_uintmax_t umval;

    /* Look at current arg; at end of the list? */
    arg = NULL;
    p = argv[opt_index];
    if (p == NULL)
        return 0;

    /* If word doesn't start with a -, we're done. */
    if (*p != '-')
        return 0;

    /* Hit "--" ? We're done. */
    opt_index++;
    if (strcmp(p, "--") == 0)
        return 0;

    /* Allow -nnn and --nnn */
    if (*++p == '-')
        p++;
    flag = p - 1;

    /* If we have --flag=foo, snip it off */
    if ((arg = strchr(p, '=')) != NULL)
        *arg++ = '\0';
    for (o = opts; o->name; ++o) {
        /* If not this option, move on to the next one. */
        if (strcmp(p, o->name) != 0)
            continue;

        /* If it doesn't take a value, make sure none was given. */
        if (o->valtype == 0 || o->valtype == '-') {
            if (arg) {
                BIO_printf(bio_err,
                           "%s: Option -%s does not take a value\n", prog, p);
                return -1;
            }
            return o->retval;
        }

        /* Want a value; get the next param if =foo not used. */
        if (arg == NULL) {
            if (argv[opt_index] == NULL) {
                BIO_printf(bio_err,
                           "%s: Option -%s needs a value\n", prog, o->name);
                return -1;
            }
            arg = argv[opt_index++];
        }

        /* Syntax-check value. */
        switch (o->valtype) {
        default:
        case 's':
            /* Just a string. */
            break;
        case '/':
            if (app_isdir(arg) > 0)
                break;
            BIO_printf(bio_err, "%s: Not a directory: %s\n", prog, arg);
            return -1;
        case '<':
            /* Input file. */
            break;
        case '>':
            /* Output file. */
            break;
        case 'p':
        case 'n':
            if (!opt_int(arg, &ival)
                    || (o->valtype == 'p' && ival <= 0)) {
                BIO_printf(bio_err,
                           "%s: Non-positive number \"%s\" for -%s\n",
                           prog, arg, o->name);
                return -1;
            }
            break;
        case 'M':
            if (!opt_imax(arg, &imval)) {
                BIO_printf(bio_err,
                           "%s: Invalid number \"%s\" for -%s\n",
                           prog, arg, o->name);
                return -1;
            }
            break;
        case 'U':
            if (!opt_umax(arg, &umval)) {
                BIO_printf(bio_err,
                           "%s: Invalid number \"%s\" for -%s\n",
                           prog, arg, o->name);
                return -1;
            }
            break;
        case 'l':
            if (!opt_long(arg, &lval)) {
                BIO_printf(bio_err,
                           "%s: Invalid number \"%s\" for -%s\n",
                           prog, arg, o->name);
                return -1;
            }
            break;
        case 'u':
            if (!opt_ulong(arg, &ulval)) {
                BIO_printf(bio_err,
                           "%s: Invalid number \"%s\" for -%s\n",
                           prog, arg, o->name);
                return -1;
            }
            break;
        case 'c':
        case 'E':
        case 'F':
        case 'f':
            if (opt_format(arg,
                           o->valtype == 'c' ? OPT_FMT_PDS :
                           o->valtype == 'E' ? OPT_FMT_PDE :
                           o->valtype == 'F' ? OPT_FMT_PEMDER
                           : OPT_FMT_ANY, &ival))
                break;
            BIO_printf(bio_err,
                       "%s: Invalid format \"%s\" for -%s\n",
                       prog, arg, o->name);
            return -1;
        }

        /* Return the flag value. */
        return o->retval;
    }
    if (unknown != NULL) {
        dunno = p;
        return unknown->retval;
    }
    BIO_printf(bio_err, "%s: Option unknown option -%s\n", prog, p);
    return -1;
}