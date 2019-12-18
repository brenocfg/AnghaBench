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
 int EINVAL ; 
 int /*<<< orphan*/  WDOG_PRETIMEOUT_MSG_INT ; 
 int /*<<< orphan*/  WDOG_PRETIMEOUT_NMI ; 
 int /*<<< orphan*/  WDOG_PRETIMEOUT_NONE ; 
 int /*<<< orphan*/  WDOG_PRETIMEOUT_SMI ; 
 char* preaction ; 
 int /*<<< orphan*/  preaction_val ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 

__attribute__((used)) static int preaction_op(const char *inval, char *outval)
{
	if (outval)
		strcpy(outval, preaction);

	if (!inval)
		return 0;

	if (strcmp(inval, "pre_none") == 0)
		preaction_val = WDOG_PRETIMEOUT_NONE;
	else if (strcmp(inval, "pre_smi") == 0)
		preaction_val = WDOG_PRETIMEOUT_SMI;
#ifdef HAVE_DIE_NMI
	else if (strcmp(inval, "pre_nmi") == 0)
		preaction_val = WDOG_PRETIMEOUT_NMI;
#endif
	else if (strcmp(inval, "pre_int") == 0)
		preaction_val = WDOG_PRETIMEOUT_MSG_INT;
	else
		return -EINVAL;
	strcpy(preaction, inval);
	return 0;
}