#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * pzBugAddr; int /*<<< orphan*/ * pzPackager; int /*<<< orphan*/ * pzCopyNotice; int /*<<< orphan*/ * pzCopyright; } ;
typedef  TYPE_1__ tOptions ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ HAS_pzPkgDataDir (TYPE_1__*) ; 
 int /*<<< orphan*/  NL ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fputc (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fputs (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * optionVersion () ; 
 char* zPlsSendBugs ; 
 char* zao_ver_fmt ; 

__attribute__((used)) static void
emit_copy_note(tOptions * opts, FILE * fp)
{
    if (opts->pzCopyright != NULL)
        fputs(opts->pzCopyright, fp);

    if (opts->pzCopyNotice != NULL)
        fputs(opts->pzCopyNotice, fp);

    fputc(NL, fp);
    fprintf(fp, zao_ver_fmt, optionVersion());
    
    if (HAS_pzPkgDataDir(opts) && (opts->pzPackager != NULL)) {
        fputc(NL, fp);
        fputs(opts->pzPackager, fp);

    } else if (opts->pzBugAddr != NULL) {
        fputc(NL, fp);
        fprintf(fp, zPlsSendBugs, opts->pzBugAddr);
    }
}