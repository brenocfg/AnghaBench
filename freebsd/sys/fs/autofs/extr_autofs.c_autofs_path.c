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
struct autofs_node {char* an_name; struct autofs_node* an_parent; struct autofs_mount* an_mount; } ;
struct autofs_mount {char* am_mountpoint; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_AUTOFS ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  free (char*,int /*<<< orphan*/ ) ; 
 char* malloc (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 char* strdup (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static char *
autofs_path(struct autofs_node *anp)
{
	struct autofs_mount *amp;
	char *path, *tmp;

	amp = anp->an_mount;

	path = strdup("", M_AUTOFS);
	for (; anp->an_parent != NULL; anp = anp->an_parent) {
		tmp = malloc(strlen(anp->an_name) + strlen(path) + 2,
		    M_AUTOFS, M_WAITOK);
		strcpy(tmp, anp->an_name);
		strcat(tmp, "/");
		strcat(tmp, path);
		free(path, M_AUTOFS);
		path = tmp;
	}

	tmp = malloc(strlen(amp->am_mountpoint) + strlen(path) + 2,
	    M_AUTOFS, M_WAITOK);
	strcpy(tmp, amp->am_mountpoint);
	strcat(tmp, "/");
	strcat(tmp, path);
	free(path, M_AUTOFS);
	path = tmp;

	return (path);
}