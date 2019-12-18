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
 int /*<<< orphan*/  endusershell () ; 
 char* getusershell () ; 
 int /*<<< orphan*/  setusershell () ; 
 scalar_t__ strcmp (char*,char const*) ; 

__attribute__((used)) static int
chshell(const char *sh)
{
	int r;
	char *cp;

	r = 0;
	setusershell();
	while ((cp = getusershell()) != NULL && !r)
	    r = (strcmp(cp, sh) == 0);
	endusershell();
	return r;
}