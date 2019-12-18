#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tSuccess ;
struct TYPE_5__ {int fOptSet; int /*<<< orphan*/  (* pUsageProc ) (TYPE_1__*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  pzProgPath; } ;
typedef  TYPE_1__ tOptions ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  FAILURE ; 
 int OPTPROC_ERRSTOP ; 
 int /*<<< orphan*/  _exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  opt_ambiguities (TYPE_1__*,char const*,int) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strlen (char const*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ ) ; 
 char* zambig_opt_fmt ; 

__attribute__((used)) static tSuccess
opt_ambiguous(tOptions * opts, char const * name, int match_ct)
{
    if ((opts->fOptSet & OPTPROC_ERRSTOP) != 0) {
        fprintf(stderr, zambig_opt_fmt, opts->pzProgPath, name, match_ct);
        if (match_ct <= 4)
            opt_ambiguities(opts, name, (int)strlen(name));
        (*opts->pUsageProc)(opts, EXIT_FAILURE);
        /* NOTREACHED */
        _exit(EXIT_FAILURE); /* to be certain */
    }
    return FAILURE;
}