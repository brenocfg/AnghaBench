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
 scalar_t__ blklevel ; 
 int /*<<< orphan*/ * expmatch (char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  l_prcbeg ; 
 int /*<<< orphan*/  l_toplex ; 
 char* pname ; 

__attribute__((used)) static bool
isproc(char *s)
{
    pname[0] = '\0';
    if (!l_toplex || blklevel == 0)
	if (expmatch(s, l_prcbeg, pname) != NULL) {
	    return (true);
	}
    return (false);
}