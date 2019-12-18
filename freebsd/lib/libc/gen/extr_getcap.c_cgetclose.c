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
 int /*<<< orphan*/ * dbp ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ gottoprec ; 
 int /*<<< orphan*/ * pfp ; 
 scalar_t__ slash ; 

int
cgetclose(void)
{
	if (pfp != NULL) {
		(void)fclose(pfp);
		pfp = NULL;
	}
	dbp = NULL;
	gottoprec = 0;
	slash = 0;
	return(0);
}