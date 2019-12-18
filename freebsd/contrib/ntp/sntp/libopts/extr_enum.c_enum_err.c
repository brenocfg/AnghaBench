#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  (* pUsageProc ) (TYPE_2__*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  pzProgName; } ;
typedef  TYPE_2__ tOptions ;
struct TYPE_8__ {int /*<<< orphan*/  argString; } ;
struct TYPE_10__ {int /*<<< orphan*/  fOptState; int /*<<< orphan*/  pz_Name; TYPE_1__ optArg; } ;
typedef  TYPE_3__ tOptDesc ;

/* Variables and functions */
 char* ENUM_ERR_LINE ; 
 char* ENUM_ERR_WIDTH ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 char NL ; 
 char* NLSTR_FMT ; 
 char* NLSTR_SPACE_FMT ; 
 scalar_t__ OPARG_TYPE_MEMBERSHIP ; 
 TYPE_2__* OPTPROC_EMIT_LIMIT ; 
 scalar_t__ OPTST_GET_ARGTYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TWO_SPACES_STR ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  fputc (char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fputs (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  option_usage_fp ; 
 char* pz_enum_err_fmt ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ ) ; 
 char* zIntRange ; 
 char* zLowerBits ; 
 int /*<<< orphan*/  zSetMemberSettings ; 
 char* zValidKeys ; 

__attribute__((used)) static void
enum_err(tOptions * pOpts, tOptDesc * pOD,
         char const * const * paz_names, int name_ct)
{
    size_t max_len = 0;
    size_t ttl_len = 0;
    int    ct_down = name_ct;
    int    hidden  = 0;

    /*
     *  A real "pOpts" pointer means someone messed up.  Give a real error.
     */
    if (pOpts > OPTPROC_EMIT_LIMIT)
        fprintf(option_usage_fp, pz_enum_err_fmt, pOpts->pzProgName,
                pOD->optArg.argString, pOD->pz_Name);

    fprintf(option_usage_fp, zValidKeys, pOD->pz_Name);

    /*
     *  If the first name starts with this funny character, then we have
     *  a first value with an unspellable name.  You cannot specify it.
     *  So, we don't list it either.
     */
    if (**paz_names == 0x7F) {
        paz_names++;
        hidden  = 1;
        ct_down = --name_ct;
    }

    /*
     *  Figure out the maximum length of any name, plus the total length
     *  of all the names.
     */
    {
        char const * const * paz = paz_names;

        do  {
            size_t len = strlen(*(paz++)) + 1;
            if (len > max_len)
                max_len = len;
            ttl_len += len;
        } while (--ct_down > 0);

        ct_down = name_ct;
    }

    /*
     *  IF any one entry is about 1/2 line or longer, print one per line
     */
    if (max_len > 35) {
        do  {
            fprintf(option_usage_fp, ENUM_ERR_LINE, *(paz_names++));
        } while (--ct_down > 0);
    }

    /*
     *  ELSE IF they all fit on one line, then do so.
     */
    else if (ttl_len < 76) {
        fputc(' ', option_usage_fp);
        do  {
            fputc(' ', option_usage_fp);
            fputs(*(paz_names++), option_usage_fp);
        } while (--ct_down > 0);
        fputc(NL, option_usage_fp);
    }

    /*
     *  Otherwise, columnize the output
     */
    else {
        unsigned int ent_no = 0;
        char  zFmt[16];  /* format for all-but-last entries on a line */

        sprintf(zFmt, ENUM_ERR_WIDTH, (int)max_len);
        max_len = 78 / max_len; /* max_len is now max entries on a line */
        fputs(TWO_SPACES_STR, option_usage_fp);

        /*
         *  Loop through all but the last entry
         */
        ct_down = name_ct;
        while (--ct_down > 0) {
            if (++ent_no == max_len) {
                /*
                 *  Last entry on a line.  Start next line, too.
                 */
                fprintf(option_usage_fp, NLSTR_SPACE_FMT, *(paz_names++));
                ent_no = 0;
            }

            else
                fprintf(option_usage_fp, zFmt, *(paz_names++) );
        }
        fprintf(option_usage_fp, NLSTR_FMT, *paz_names);
    }

    if (pOpts > OPTPROC_EMIT_LIMIT) {
        fprintf(option_usage_fp, zIntRange, hidden, name_ct - 1 + hidden);

        (*(pOpts->pUsageProc))(pOpts, EXIT_FAILURE);
        /* NOTREACHED */
    }

    if (OPTST_GET_ARGTYPE(pOD->fOptState) == OPARG_TYPE_MEMBERSHIP) {
        fprintf(option_usage_fp, zLowerBits, name_ct);
        fputs(zSetMemberSettings, option_usage_fp);
    } else {
        fprintf(option_usage_fp, zIntRange, hidden, name_ct - 1 + hidden);
    }
}