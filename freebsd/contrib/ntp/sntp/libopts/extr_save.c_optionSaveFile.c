#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {int presetOptCt; TYPE_3__* pOptDesc; } ;
typedef  TYPE_2__ tOptions ;
struct TYPE_16__ {int /*<<< orphan*/  argBool; int /*<<< orphan*/  argInt; } ;
struct TYPE_18__ {int fOptState; scalar_t__ optEquivIndex; scalar_t__ optIndex; int optActualIndex; TYPE_1__ optArg; } ;
typedef  TYPE_3__ tOptDesc ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ NO_EQUIVALENT ; 
#define  OPARG_TYPE_BOOLEAN 135 
#define  OPARG_TYPE_ENUMERATION 134 
#define  OPARG_TYPE_FILE 133 
#define  OPARG_TYPE_HIERARCHY 132 
#define  OPARG_TYPE_MEMBERSHIP 131 
#define  OPARG_TYPE_NONE 130 
#define  OPARG_TYPE_NUMERIC 129 
#define  OPARG_TYPE_STRING 128 
 int OPTST_DO_NOT_SAVE_MASK ; 
 int OPTST_EQUIVALENCE ; 
 int OPTST_GET_ARGTYPE (int) ; 
 scalar_t__ UNUSED_OPT (TYPE_3__*) ; 
 char* VOIDP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * open_sv_file (TYPE_2__*) ; 
 int /*<<< orphan*/  prt_entry (int /*<<< orphan*/ *,TYPE_3__*,char*) ; 
 int /*<<< orphan*/  prt_enum_arg (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  prt_file_arg (int /*<<< orphan*/ *,TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  prt_nested (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  prt_no_arg_opt (int /*<<< orphan*/ *,TYPE_3__*,TYPE_3__*) ; 
 int /*<<< orphan*/  prt_set_arg (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  prt_str_arg (int /*<<< orphan*/ *,TYPE_3__*) ; 

void
optionSaveFile(tOptions * opts)
{
    tOptDesc *  od;
    int         ct;
    FILE *      fp = open_sv_file(opts);

    if (fp == NULL)
        return;

    /*
     *  FOR each of the defined options, ...
     */
    ct = opts->presetOptCt;
    od = opts->pOptDesc;
    do  {
        tOptDesc * p;

        /*
         *  IF    the option has not been defined
         *     OR it does not take an initialization value
         *     OR it is equivalenced to another option
         *  THEN continue (ignore it)
         *
         *  Equivalenced options get picked up when the equivalenced-to
         *  option is processed.
         */
        if (UNUSED_OPT(od))
            continue;

        if ((od->fOptState & OPTST_DO_NOT_SAVE_MASK) != 0)
            continue;

        if (  (od->optEquivIndex != NO_EQUIVALENT)
           && (od->optEquivIndex != od->optIndex))
            continue;

        /*
         *  The option argument data are found at the equivalenced-to option,
         *  but the actual option argument type comes from the original
         *  option descriptor.  Be careful!
         */
        p = ((od->fOptState & OPTST_EQUIVALENCE) != 0)
            ? (opts->pOptDesc + od->optActualIndex) : od;

        switch (OPTST_GET_ARGTYPE(od->fOptState)) {
        case OPARG_TYPE_NONE:
            prt_no_arg_opt(fp, p, od);
            break;

        case OPARG_TYPE_NUMERIC:
            prt_entry(fp, p, VOIDP(p->optArg.argInt));
            break;

        case OPARG_TYPE_STRING:
            prt_str_arg(fp, p);
            break;

        case OPARG_TYPE_ENUMERATION:
            prt_enum_arg(fp, p);
            break;

        case OPARG_TYPE_MEMBERSHIP:
            prt_set_arg(fp, p);
            break;

        case OPARG_TYPE_BOOLEAN:
            prt_entry(fp, p, p->optArg.argBool ? "true" : "false");
            break;

        case OPARG_TYPE_HIERARCHY:
            prt_nested(fp, p);
            break;

        case OPARG_TYPE_FILE:
            prt_file_arg(fp, p, opts);
            break;

        default:
            break; /* cannot handle - skip it */
        }
    } while (od++, (--ct > 0));

    fclose(fp);
}