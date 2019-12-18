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
 size_t MANDOCLEVEL_OK ; 
 int /*<<< orphan*/ * fileptr ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char*,char*) ; 
 char* getprogname () ; 
 char** level_name ; 
 size_t rc ; 

void
mandoc_msg_summary(void)
{
	if (fileptr != NULL && rc != MANDOCLEVEL_OK)
		fprintf(fileptr,
		    "%s: see above the output for %s messages\n",
		    getprogname(), level_name[rc]);
}