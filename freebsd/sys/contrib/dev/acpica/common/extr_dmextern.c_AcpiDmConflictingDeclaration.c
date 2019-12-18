#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
AcpiDmConflictingDeclaration (
    char                    *Path)
{
    fprintf (stderr,
        " Warning - Emitting ASL code \"External (%s)\"\n"
        "           This is a conflicting declaration with some "
        "other declaration within the ASL code.\n"
        "           This external declaration may need to be "
        "deleted in order to recompile the dsl file.\n\n",
        Path);
}