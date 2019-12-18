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
 char** environ_pam ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ ok_to_export (char*) ; 
 int /*<<< orphan*/  setenv (char*,char*,int) ; 
 char* strchr (char*,char) ; 

__attribute__((used)) static void
export_pam_environment(void)
{
	char	**pp;
	char	*p;

	for (pp = environ_pam; *pp != NULL; pp++) {
		if (ok_to_export(*pp)) {
			p = strchr(*pp, '=');
			*p = '\0';
			setenv(*pp, p + 1, 1);
		}
		free(*pp);
	}
}