#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  SCR ;

/* Variables and functions */
 int /*<<< orphan*/  M_ERR ; 
 char* O_STR (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  msgq_wstr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* optlist ; 

int
opts_empty(
	SCR *sp,
	int off,
	int silent)
{
	char *p;

	if ((p = O_STR(sp, off)) == NULL || p[0] == '\0') {
		if (!silent)
			msgq_wstr(sp, M_ERR, optlist[off].name,
			    "305|No %s edit option specified");
		return (1);
	}
	return (0);
}