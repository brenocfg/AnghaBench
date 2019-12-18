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
struct TYPE_4__ {int /*<<< orphan*/ * pzBugAddr; int /*<<< orphan*/ * pzPackager; int /*<<< orphan*/  pzUsageTitle; int /*<<< orphan*/ * pzFullVersion; int /*<<< orphan*/ * pzCopyright; } ;
typedef  TYPE_1__ tOptions ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ HAS_pzPkgDataDir (TYPE_1__*) ; 
 int /*<<< orphan*/  NL ; 
 int /*<<< orphan*/  emit_first_line (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fputc (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fputs (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* zPlsSendBugs ; 

__attribute__((used)) static void
emit_copy_full(tOptions * o, FILE * fp)
{
    if (o->pzCopyright != NULL)
        fputs(o->pzCopyright, fp);

    else if (o->pzFullVersion != NULL)
        fputs(o->pzFullVersion, fp);

    else
        emit_first_line(fp, o->pzUsageTitle, NULL, NULL);
    
    if (HAS_pzPkgDataDir(o) && (o->pzPackager != NULL)) {
        fputc(NL, fp);
        fputs(o->pzPackager, fp);

    } else if (o->pzBugAddr != NULL) {
        fputc(NL, fp);
        fprintf(fp, zPlsSendBugs, o->pzBugAddr);
    }
}