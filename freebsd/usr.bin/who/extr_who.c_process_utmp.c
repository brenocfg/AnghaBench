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
struct utmpx {scalar_t__ ut_type; int /*<<< orphan*/  ut_line; } ;

/* Variables and functions */
 scalar_t__ BOOT_TIME ; 
 scalar_t__ USER_PROCESS ; 
 scalar_t__ aflag ; 
 scalar_t__ bflag ; 
 struct utmpx* getutxent () ; 
 int /*<<< orphan*/  row (struct utmpx*) ; 
 scalar_t__ ttystat (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
process_utmp(void)
{
	struct utmpx *utx;

	while ((utx = getutxent()) != NULL) {
		if (((aflag || !bflag) && utx->ut_type == USER_PROCESS) ||
		    (bflag && utx->ut_type == BOOT_TIME))
			if (ttystat(utx->ut_line) == 0)
				row(utx);
	}
}