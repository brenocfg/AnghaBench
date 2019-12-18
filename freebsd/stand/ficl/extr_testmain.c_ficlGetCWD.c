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
typedef  int /*<<< orphan*/  FICL_VM ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 char* getcwd (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vmTextOut (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static void ficlGetCWD(FICL_VM *pVM)
{
    char *cp;

    cp = getcwd(NULL, 80);
    vmTextOut(pVM, cp, 1);
    free(cp);
    return;
}