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
struct TYPE_5__ {char* pz_DisableName; char* pz_Name; } ;
typedef  TYPE_1__ tOptDesc ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ DISABLED_OPT (TYPE_1__*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char const*) ; 

__attribute__((used)) static void
prt_no_arg_opt(FILE * fp, tOptDesc * p, tOptDesc * pOD)
{
    /*
     * The aliased to argument indicates whether or not the option
     * is "disabled".  However, the original option has the name
     * string, so we get that there, not with "p".
     */
    char const * pznm =
        (DISABLED_OPT(p)) ? pOD->pz_DisableName : pOD->pz_Name;
    /*
     *  If the option was disabled and the disablement name is NULL,
     *  then the disablement was caused by aliasing.
     *  Use the name as the string to emit.
     */
    if (pznm == NULL)
        pznm = pOD->pz_Name;

    fprintf(fp, "%s\n", pznm);
}