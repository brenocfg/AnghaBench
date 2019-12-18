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
 char* _PATH_DEV ; 
 int /*<<< orphan*/  isdigit (char) ; 
 int strlen (char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 int strtoul (char*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
resolve_ccdname(char *name)
{

	if (!strncmp(name, _PATH_DEV, strlen(_PATH_DEV)))
		name += strlen(_PATH_DEV);
	if (strncmp(name, "ccd", 3))
		return -1;
	name += 3;
	if (!isdigit(*name))
		return -1;
	return (strtoul(name, NULL, 10));
}