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
struct TYPE_7__ {int fOptSet; } ;
typedef  TYPE_1__ tOptions ;
struct TYPE_8__ {int optValue; } ;
typedef  TYPE_2__ tOptDesc ;
struct TYPE_9__ {char* pzSpc; char* pzNoF; } ;
typedef  TYPE_3__ arg_types_t ;

/* Variables and functions */
 int /*<<< orphan*/  IS_GRAPHIC_CHAR (int) ; 
 int OPTPROC_GNUUSAGE ; 
 int OPTPROC_LONGOPT ; 
 int OPTPROC_SHORTOPT ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  fputc (char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  option_usage_fp ; 

__attribute__((used)) static void
prt_preamble(tOptions * opts, tOptDesc * od, arg_types_t * at)
{
    /*
     *  Flag prefix: IF no flags at all, then omit it.  If not printable
     *  (not allowed for this option), then blank, else print it.
     *  Follow it with a comma if we are doing GNU usage and long
     *  opts are to be printed too.
     */
    if ((opts->fOptSet & OPTPROC_SHORTOPT) == 0)
        fputs(at->pzSpc, option_usage_fp);

    else if (! IS_GRAPHIC_CHAR(od->optValue)) {
        if (  (opts->fOptSet & (OPTPROC_GNUUSAGE|OPTPROC_LONGOPT))
           == (OPTPROC_GNUUSAGE|OPTPROC_LONGOPT))
            fputc(' ', option_usage_fp);
        fputs(at->pzNoF, option_usage_fp);

    } else {
        fprintf(option_usage_fp, "   -%c", od->optValue);
        if (  (opts->fOptSet & (OPTPROC_GNUUSAGE|OPTPROC_LONGOPT))
           == (OPTPROC_GNUUSAGE|OPTPROC_LONGOPT))
            fputs(", ", option_usage_fp);
    }
}