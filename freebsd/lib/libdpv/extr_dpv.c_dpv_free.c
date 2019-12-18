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
 int /*<<< orphan*/ * aprompt ; 
 int /*<<< orphan*/  dialog_maxsize_free () ; 
 int /*<<< orphan*/  dialogrc_free () ; 
 int /*<<< orphan*/  dprompt_free () ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pprompt ; 
 int /*<<< orphan*/  status_free () ; 

void
dpv_free(void)
{
	dialogrc_free();
	dprompt_free();
	dialog_maxsize_free();
	if (aprompt != NULL) {
		free(aprompt);
		aprompt = NULL;
	}
	if (pprompt != NULL) {
		free(pprompt);
		pprompt = NULL;
	}
	status_free();
}