#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int fOptSet; int /*<<< orphan*/  pzProgName; } ;
typedef  TYPE_2__ tOptions ;
struct TYPE_11__ {int* argString; } ;
struct TYPE_13__ {int fOptState; TYPE_1__ optArg; } ;
typedef  TYPE_3__ tOptDesc ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  EXIT_SUCCESS ; 
#define  NUL 128 
 TYPE_2__* OPTPROC_EMIT_LIMIT ; 
 int OPTPROC_GNUUSAGE ; 
 int OPTST_ARG_OPTIONAL ; 
 int /*<<< orphan*/  emit_copy_full (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  emit_copy_note (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  emit_simple_ver (TYPE_2__*,int /*<<< orphan*/ *) ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char) ; 
 int /*<<< orphan*/  fserr_exit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  option_exits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_usage_flags (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/ * stdout ; 
 char* zBadVerArg ; 
 int /*<<< orphan*/  zstderr_name ; 
 int /*<<< orphan*/  zstdout_name ; 
 int /*<<< orphan*/  zwriting ; 

__attribute__((used)) static void
print_ver(tOptions * opts, tOptDesc * od, FILE * fp, bool call_exit)
{
    char ch;

    if (opts <= OPTPROC_EMIT_LIMIT)
        return;

    /*
     *  IF we have an argument for this option, use it
     *  Otherwise, default to version only or copyright note,
     *  depending on whether the layout is GNU standard form or not.
     */
    if (  (od->fOptState & OPTST_ARG_OPTIONAL)
       && (od->optArg.argString != NULL)
       && (od->optArg.argString[0] != NUL))

        ch = od->optArg.argString[0];

    else {
        set_usage_flags(opts, NULL);
        ch = (opts->fOptSet & OPTPROC_GNUUSAGE) ? 'c' : 'v';
    }

    switch (ch) {
    case NUL: /* arg provided, but empty */
    case 'v': case 'V': emit_simple_ver(opts, fp); break;
    case 'c': case 'C': emit_copy_full( opts, fp); break;
    case 'n': case 'N': emit_copy_note( opts, fp); break;

    default:
        fprintf(stderr, zBadVerArg, ch);
        option_exits(EXIT_FAILURE);
    }

    fflush(fp);
    if (ferror(fp))
        fserr_exit(opts->pzProgName, zwriting,
                   (fp == stdout) ? zstdout_name : zstderr_name);

    if (call_exit)
        option_exits(EXIT_SUCCESS);
}