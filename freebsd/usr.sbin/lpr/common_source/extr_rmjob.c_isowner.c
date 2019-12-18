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
 scalar_t__ from_host ; 
 scalar_t__ local_host ; 
 scalar_t__ person ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 char const* root ; 
 int /*<<< orphan*/  strcmp (scalar_t__,char const*) ; 

__attribute__((used)) static int
isowner(char *owner, char *file, const char *cfhost)
{
	if (!strcmp(person, root) && (from_host == local_host ||
	    !strcmp(from_host, cfhost)))
		return (1);
	if (!strcmp(person, owner) && !strcmp(from_host, cfhost))
		return (1);
	if (from_host != local_host)
		printf("%s: ", local_host);
	printf("%s: Permission denied\n", file);
	return(0);
}