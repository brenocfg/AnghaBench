#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int optCt; int fOptSet; int presetOptCt; TYPE_2__* pOptDesc; } ;
typedef  TYPE_1__ tOptions ;
struct TYPE_14__ {int fOptState; char* pz_Name; char* pzText; int /*<<< orphan*/  optValue; } ;
typedef  TYPE_2__ tOptDesc ;
struct TYPE_15__ {char* pzBrk; } ;

/* Variables and functions */
 int EXIT_SUCCESS ; 
 int /*<<< orphan*/  IS_GRAPHIC_CHAR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NL ; 
 int OPTPROC_VENDOR_OPT ; 
 int OPTST_DOCUMENT ; 
 int OPTST_NO_INIT ; 
 int OPTST_NO_USAGE_MASK ; 
 int OPTST_OMITTED ; 
 TYPE_5__ argTypes ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char const*) ; 
 int /*<<< orphan*/  fputc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  option_usage_fp ; 
 int /*<<< orphan*/  prt_extd_usage (TYPE_1__*,TYPE_2__*,char const*) ; 
 int /*<<< orphan*/  prt_one_usage (TYPE_1__*,TYPE_2__*,TYPE_5__*) ; 
 int /*<<< orphan*/  prt_preamble (TYPE_1__*,TYPE_2__*,TYPE_5__*) ; 
 char* zAuto ; 
 char* zDisabledOpt ; 
 char* zDisabledWhy ; 
 char* zVendIntro ; 

__attribute__((used)) static void
prt_opt_usage(tOptions * opts, int ex_code, char const * title)
{
    int         ct     = opts->optCt;
    int         optNo  = 0;
    tOptDesc *  od     = opts->pOptDesc;
    int         docCt  = 0;

    do  {
        /*
         * no usage --> disallowed on command line (OPTST_NO_COMMAND), or
         * deprecated -- strongly discouraged (OPTST_DEPRECATED), or
         * compiled out of current object code (OPTST_OMITTED)
         */
        if ((od->fOptState & OPTST_NO_USAGE_MASK) != 0) {

            /*
             * IF      this is a compiled-out option
             *   *AND* usage was requested with "omitted-usage"
             *   *AND* this is NOT abbreviated usage
             * THEN display this option.
             */
            if (  (od->fOptState == (OPTST_OMITTED | OPTST_NO_INIT))
               && (od->pz_Name != NULL)
               && (ex_code == EXIT_SUCCESS))  {

                char const * why_pz =
                    (od->pzText == NULL) ? zDisabledWhy : od->pzText;
                prt_preamble(opts, od, &argTypes);
                fprintf(option_usage_fp, zDisabledOpt, od->pz_Name, why_pz);
            }

            continue;
        }

        if ((od->fOptState & OPTST_DOCUMENT) != 0) {
            if (ex_code == EXIT_SUCCESS) {
                fprintf(option_usage_fp, argTypes.pzBrk, od->pzText,
                        title);
                docCt++;
            }

            continue;
        }

        /* Skip name only options when we have a vendor option */
        if (  ((opts->fOptSet & OPTPROC_VENDOR_OPT) != 0)
           && (! IS_GRAPHIC_CHAR(od->optValue)))
            continue;

        /*
         *  IF       this is the first auto-opt maintained option
         *    *AND*  we are doing a full help
         *    *AND*  there are documentation options
         *    *AND*  the last one was not a doc option,
         *  THEN document that the remaining options are not user opts
         */
        if ((docCt > 0) && (ex_code == EXIT_SUCCESS)) {
            if (opts->presetOptCt == optNo) {
                if ((od[-1].fOptState & OPTST_DOCUMENT) == 0)
                    fprintf(option_usage_fp, argTypes.pzBrk, zAuto, title);

            } else if ((ct == 1) &&
                       (opts->fOptSet & OPTPROC_VENDOR_OPT))
                fprintf(option_usage_fp, argTypes.pzBrk, zVendIntro, title);
        }

        prt_one_usage(opts, od, &argTypes);

        /*
         *  IF we were invoked because of the --help option,
         *  THEN print all the extra info
         */
        if (ex_code == EXIT_SUCCESS)
            prt_extd_usage(opts, od, title);

    } while (od++, optNo++, (--ct > 0));

    fputc(NL, option_usage_fp);
}