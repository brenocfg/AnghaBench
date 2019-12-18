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
typedef  int pam_control_t ;

/* Variables and functions */
 int PAM_NUM_CONTROL_FLAGS ; 
 int /*<<< orphan*/ * pam_control_flag_name ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static pam_control_t
parse_control_flag(const char *name)
{
	int i;

	for (i = 0; i < PAM_NUM_CONTROL_FLAGS; ++i)
		if (strcmp(pam_control_flag_name[i], name) == 0)
			return (i);
	return ((pam_control_t)-1);
}