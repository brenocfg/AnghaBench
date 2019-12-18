#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int presetOptCt; int /*<<< orphan*/  pzPROGNAME; TYPE_3__* pOptDesc; } ;
typedef  TYPE_2__ tOptions ;
struct TYPE_7__ {char* argString; int /*<<< orphan*/  argBool; scalar_t__ argIntptr; scalar_t__ argInt; } ;
struct TYPE_9__ {int optMaxCt; int /*<<< orphan*/ * pz_NAME; TYPE_1__ optArg; int /*<<< orphan*/  (* pOptProc ) (int /*<<< orphan*/ ,TYPE_3__*) ;int /*<<< orphan*/  fOptState; } ;
typedef  TYPE_3__ tOptDesc ;
typedef  int /*<<< orphan*/  int_val_buf ;

/* Variables and functions */
 char* FALSE_STR ; 
 char* MULTI_DEF_FMT ; 
#define  OPARG_TYPE_BOOLEAN 131 
#define  OPARG_TYPE_ENUMERATION 130 
#define  OPARG_TYPE_MEMBERSHIP 129 
#define  OPARG_TYPE_NUMERIC 128 
 int /*<<< orphan*/  OPTPROC_EMIT_SHELL ; 
 int OPTST_GET_ARGTYPE (int /*<<< orphan*/ ) ; 
 char const* SGL_DEF_FMT ; 
 char* SGL_NO_DEF_FMT ; 
 scalar_t__ SKIP_OPT (TYPE_3__*) ; 
 char* TRUE_STR ; 
 int /*<<< orphan*/  printf (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,unsigned long) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_3__*) ; 

__attribute__((used)) static void
emit_setup(tOptions * opts)
{
    tOptDesc *   od     = opts->pOptDesc;
    int          opt_ct = opts->presetOptCt;
    char const * fmt;
    char const * def_val;

    for (;opt_ct > 0; od++, --opt_ct) {
        char int_val_buf[32];

        /*
         *  Options that are either usage documentation or are compiled out
         *  are not to be processed.
         */
        if (SKIP_OPT(od) || (od->pz_NAME == NULL))
            continue;

        if (od->optMaxCt > 1)
             fmt = MULTI_DEF_FMT;
        else fmt = SGL_DEF_FMT;

        /*
         *  IF this is an enumeration/bitmask option, then convert the value
         *  to a string before printing the default value.
         */
        switch (OPTST_GET_ARGTYPE(od->fOptState)) {
        case OPARG_TYPE_ENUMERATION:
            (*(od->pOptProc))(OPTPROC_EMIT_SHELL, od );
            def_val = od->optArg.argString;
            break;

        /*
         *  Numeric and membership bit options are just printed as a number.
         */
        case OPARG_TYPE_NUMERIC:
            snprintf(int_val_buf, sizeof(int_val_buf), "%d",
                     (int)od->optArg.argInt);
            def_val = int_val_buf;
            break;

        case OPARG_TYPE_MEMBERSHIP:
            snprintf(int_val_buf, sizeof(int_val_buf), "%lu",
                     (unsigned long)od->optArg.argIntptr);
            def_val = int_val_buf;
            break;

        case OPARG_TYPE_BOOLEAN:
            def_val = (od->optArg.argBool) ? TRUE_STR : FALSE_STR;
            break;

        default:
            if (od->optArg.argString == NULL) {
                if (fmt == SGL_DEF_FMT)
                    fmt = SGL_NO_DEF_FMT;
                def_val = NULL;
            }
            else
                def_val = od->optArg.argString;
        }

        printf(fmt, opts->pzPROGNAME, od->pz_NAME, def_val);
    }
}