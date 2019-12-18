#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int fOptSet; char const* pzExplain; char const* pzPackager; int /*<<< orphan*/  pzProgName; int /*<<< orphan*/ * pzBugAddr; TYPE_1__* pOptDesc; } ;
typedef  TYPE_2__ tOptions ;
struct TYPE_10__ {int fOptState; } ;

/* Variables and functions */
 int EXIT_SUCCESS ; 
 scalar_t__ HAS_pzPkgDataDir (TYPE_2__*) ; 
 int /*<<< orphan*/  NL ; 
#define  OPTPROC_LONGOPT 130 
#define  OPTPROC_L_N_S 129 
 int OPTPROC_NUM_OPT ; 
 int OPTPROC_REORDER ; 
#define  OPTPROC_SHORTOPT 128 
 int OPTST_DOCUMENT ; 
 scalar_t__ do_gnu_usage (TYPE_2__*) ; 
 scalar_t__ ferror (scalar_t__) ; 
 int /*<<< orphan*/  fflush (scalar_t__) ; 
 int /*<<< orphan*/  fprintf (scalar_t__,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fputc (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  fputs (char const*,scalar_t__) ; 
 int /*<<< orphan*/  fserr_exit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  line_fmt_buf ; 
 scalar_t__ option_usage_fp ; 
 int /*<<< orphan*/  prt_opt_usage (TYPE_2__*,int,char const*) ; 
 int /*<<< orphan*/  prt_prog_detail (TYPE_2__*) ; 
 int setGnuOptFmts (TYPE_2__*,char const**) ; 
 int setStdOptFmts (TYPE_2__*,char const**) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ stderr ; 
 int tab_skip_ct ; 
 char const* zFlagOkay ; 
 char* zFmtFmt ; 
 char const* zNoFlags ; 
 char const* zNumberOpt ; 
 char const* zOptsOnly ; 
 char* zPlsSendBugs ; 
 char const* zReorder ; 
 int /*<<< orphan*/  zstderr_name ; 
 int /*<<< orphan*/  zstdout_name ; 
 int /*<<< orphan*/  zwriting ; 

__attribute__((used)) static void
print_usage_details(tOptions * opts, int exit_code)
{
    {
        char const * pOptTitle = NULL;
        int flen;

        /*
         *  Determine which header and which option formatting strings to use
         */
        if (do_gnu_usage(opts)) {
            flen = setGnuOptFmts(opts, &pOptTitle);
            sprintf(line_fmt_buf, zFmtFmt, flen);
            fputc(NL, option_usage_fp);
        }
        else {
            flen = setStdOptFmts(opts, &pOptTitle);
            sprintf(line_fmt_buf, zFmtFmt, flen);

            /*
             *  When we exit with EXIT_SUCCESS and the first option is a doc
             *  option, we do *NOT* want to emit the column headers.
             *  Otherwise, we do.
             */
            if (  (exit_code != EXIT_SUCCESS)
               || ((opts->pOptDesc->fOptState & OPTST_DOCUMENT) == 0) )

                fputs(pOptTitle, option_usage_fp);
        }

        flen = 4 - ((flen + 15) / 8);
        if (flen > 0)
            tab_skip_ct = flen;
        prt_opt_usage(opts, exit_code, pOptTitle);
    }

    /*
     *  Describe the mechanics of denoting the options
     */
    switch (opts->fOptSet & OPTPROC_L_N_S) {
    case OPTPROC_L_N_S:     fputs(zFlagOkay, option_usage_fp); break;
    case OPTPROC_SHORTOPT:  break;
    case OPTPROC_LONGOPT:   fputs(zNoFlags,  option_usage_fp); break;
    case 0:                 fputs(zOptsOnly, option_usage_fp); break;
    }

    if ((opts->fOptSet & OPTPROC_NUM_OPT) != 0)
        fputs(zNumberOpt, option_usage_fp);

    if ((opts->fOptSet & OPTPROC_REORDER) != 0)
        fputs(zReorder, option_usage_fp);

    if (opts->pzExplain != NULL)
        fputs(opts->pzExplain, option_usage_fp);

    /*
     *  IF the user is asking for help (thus exiting with SUCCESS),
     *  THEN see what additional information we can provide.
     */
    if (exit_code == EXIT_SUCCESS)
        prt_prog_detail(opts);

    /*
     * Give bug notification preference to the packager information
     */
    if (HAS_pzPkgDataDir(opts) && (opts->pzPackager != NULL))
        fputs(opts->pzPackager, option_usage_fp);

    else if (opts->pzBugAddr != NULL)
        fprintf(option_usage_fp, zPlsSendBugs, opts->pzBugAddr);

    fflush(option_usage_fp);

    if (ferror(option_usage_fp) != 0)
        fserr_exit(opts->pzProgName, zwriting, (option_usage_fp == stderr)
                   ? zstderr_name : zstdout_name);
}