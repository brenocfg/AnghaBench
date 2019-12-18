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
 int /*<<< orphan*/  WDOG_PREOP_GIVE_DATA ; 
 int /*<<< orphan*/  WDOG_PREOP_NONE ; 
 int /*<<< orphan*/  WDOG_PREOP_PANIC ; 
 char* preop ; 
 int /*<<< orphan*/  preop_val ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 

__attribute__((used)) static int preop_op(const char *inval, char *outval)
{
	if (outval)
		strcpy(outval, preop);

	if (!inval)
		return 0;

	if (strcmp(inval, "preop_none") == 0)
		preop_val = WDOG_PREOP_NONE;
	else if (strcmp(inval, "preop_panic") == 0)
		preop_val = WDOG_PREOP_PANIC;
	else if (strcmp(inval, "preop_give_data") == 0)
		preop_val = WDOG_PREOP_GIVE_DATA;
	else
		return -EINVAL;
	strcpy(preop, inval);
	return 0;
}