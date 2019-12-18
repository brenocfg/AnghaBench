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
struct moduledir {char const* d_path; } ;

/* Variables and functions */
 char* malloc (scalar_t__) ; 
 int /*<<< orphan*/  strcat (char*,char const*) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static char *
moduledir_fullpath(struct moduledir *mdp, const char *fname)
{
	char *cp;

	cp = malloc(strlen(mdp->d_path) + strlen(fname) + 2);
	if (cp == NULL)
		return NULL;
	strcpy(cp, mdp->d_path);
	strcat(cp, "/");
	strcat(cp, fname);
	return (cp);
}