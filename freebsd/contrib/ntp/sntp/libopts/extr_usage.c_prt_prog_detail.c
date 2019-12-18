#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int fOptSet; int optCt; int /*<<< orphan*/ * pzDetail; TYPE_2__* pOptDesc; int /*<<< orphan*/  pzPROGNAME; int /*<<< orphan*/  pzProgPath; int /*<<< orphan*/  pzRcName; int /*<<< orphan*/ * papzHomeList; } ;
typedef  TYPE_1__ tOptions ;
struct TYPE_6__ {int /*<<< orphan*/  (* pOptProc ) (int /*<<< orphan*/ ,TYPE_2__*) ;int /*<<< orphan*/  fOptState; } ;
typedef  TYPE_2__ tOptDesc ;

/* Variables and functions */
 int /*<<< orphan*/  NL ; 
#define  OPARG_TYPE_ENUMERATION 129 
#define  OPARG_TYPE_MEMBERSHIP 128 
 int /*<<< orphan*/  OPTPROC_EMIT_USAGE ; 
 int OPTPROC_ENVIRON ; 
 int OPTST_GET_ARGTYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ displayEnum ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fputc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fputs (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  option_usage_fp ; 
 int /*<<< orphan*/  prt_ini_list (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_2__*) ; 
 char* zExamineFmt ; 
 int /*<<< orphan*/ * zPresetIntro ; 

__attribute__((used)) static void
prt_prog_detail(tOptions * opts)
{
    bool need_intro = (opts->papzHomeList == NULL);

    /*
     *  Display all the places we look for config files, if we have
     *  a list of directories to search.
     */
    if (! need_intro)
        prt_ini_list(opts->papzHomeList, opts->pzRcName, opts->pzProgPath);

    /*
     *  Let the user know about environment variable settings
     */
    if ((opts->fOptSet & OPTPROC_ENVIRON) != 0) {
        if (need_intro)
            fputs(zPresetIntro, option_usage_fp);

        fprintf(option_usage_fp, zExamineFmt, opts->pzPROGNAME);
    }

    /*
     *  IF we found an enumeration,
     *  THEN hunt for it again.  Call the handler proc with a NULL
     *       option struct pointer.  That tells it to display the keywords.
     */
    if (displayEnum) {
        int        ct     = opts->optCt;
        int        optNo  = 0;
        tOptDesc * od     = opts->pOptDesc;

        fputc(NL, option_usage_fp);
        fflush(option_usage_fp);
        do  {
            switch (OPTST_GET_ARGTYPE(od->fOptState)) {
            case OPARG_TYPE_ENUMERATION:
            case OPARG_TYPE_MEMBERSHIP:
                (*(od->pOptProc))(OPTPROC_EMIT_USAGE, od);
            }
        } while (od++, optNo++, (--ct > 0));
    }

    /*
     *  If there is a detail string, now is the time for that.
     */
    if (opts->pzDetail != NULL)
        fputs(opts->pzDetail, option_usage_fp);
}