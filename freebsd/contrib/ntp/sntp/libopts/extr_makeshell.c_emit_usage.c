#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  time_t ;
struct TYPE_6__ {char* pzPROGNAME; int optCt; TYPE_2__* pOptDesc; int /*<<< orphan*/  pzProgName; int /*<<< orphan*/  pzProgPath; } ;
typedef  TYPE_1__ tOptions ;
struct TYPE_7__ {scalar_t__ pOptProc; } ;
typedef  TYPE_2__ tOptDesc ;
struct tm {int dummy; } ;

/* Variables and functions */
 int AO_NAME_SIZE ; 
 char* END_PRE_FMT ; 
 char* GENSHELL_OPT_ARG (int /*<<< orphan*/ ) ; 
 scalar_t__ HAVE_GENSHELL_OPT (int /*<<< orphan*/ ) ; 
 char NUL ; 
 char* PREAMBLE_FMT ; 
 int /*<<< orphan*/  SCRIPT ; 
 char* SHELL_MAGIC ; 
 int /*<<< orphan*/  START_MARK ; 
 char* STDOUT ; 
 int /*<<< orphan*/  TIME_FMT ; 
 int /*<<< orphan*/  TT_LONGUSAGE ; 
 int /*<<< orphan*/  TT_USAGE ; 
 int /*<<< orphan*/  TT_VERSION ; 
 char** VOIDP (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fputs (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct tm* localtime (int /*<<< orphan*/ *) ; 
 scalar_t__ optionPrintVersion ; 
 int /*<<< orphan*/  printf (char*,char*,...) ; 
 int /*<<< orphan*/ * script_leader ; 
 char* shell_prog ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  strftime (char*,int,int /*<<< orphan*/ ,struct tm*) ; 
 int /*<<< orphan*/  text_to_var (TYPE_1__*,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 
 scalar_t__ tolower (unsigned char) ; 

__attribute__((used)) static void
emit_usage(tOptions * opts)
{
    char tm_nm_buf[AO_NAME_SIZE];

    /*
     *  First, switch stdout to the output file name.
     *  Then, change the program name to the one defined
     *  by the definitions (rather than the current
     *  executable name).  Down case the upper cased name.
     */
    if (script_leader != NULL)
        fputs(script_leader, stdout);

    {
        char const * out_nm;

        {
            time_t    c_tim = time(NULL);
            struct tm * ptm = localtime(&c_tim);
            strftime(tm_nm_buf, AO_NAME_SIZE, TIME_FMT, ptm );
        }

        if (HAVE_GENSHELL_OPT(SCRIPT))
             out_nm = GENSHELL_OPT_ARG(SCRIPT);
        else out_nm = STDOUT;

        if ((script_leader == NULL) && (shell_prog != NULL))
            printf(SHELL_MAGIC, shell_prog);

        printf(PREAMBLE_FMT, START_MARK, out_nm, tm_nm_buf);
    }

    printf(END_PRE_FMT, opts->pzPROGNAME);

    /*
     *  Get a copy of the original program name in lower case and
     *  fill in an approximation of the program name from it.
     */
    {
        char *       pzPN = tm_nm_buf;
        char const * pz   = opts->pzPROGNAME;
        char **      pp;

        /* Copy the program name into the time/name buffer */
        for (;;) {
            if ((*pzPN++ = (char)tolower((unsigned char)*pz++)) == NUL)
                break;
        }

        pp  = VOIDP(&(opts->pzProgPath));
        *pp = tm_nm_buf;
        pp  = VOIDP(&(opts->pzProgName));
        *pp = tm_nm_buf;
    }

    text_to_var(opts, TT_LONGUSAGE, NULL);
    text_to_var(opts, TT_USAGE,     NULL);

    {
        tOptDesc * pOptDesc = opts->pOptDesc;
        int        optionCt = opts->optCt;

        for (;;) {
            if (pOptDesc->pOptProc == optionPrintVersion) {
                text_to_var(opts, TT_VERSION, pOptDesc);
                break;
            }

            if (--optionCt <= 0)
                break;
            pOptDesc++;
        }
    }
}