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
struct pfs_node {char* pn_name; struct pfs_node* pn_parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAXPATHLEN ; 
 int /*<<< orphan*/  M_TEMP ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  free (char*,int /*<<< orphan*/ ) ; 
 char* malloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,char*,char*) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int /*<<< orphan*/ ) ; 
 int strlen (char*) ; 

__attribute__((used)) static char *
get_full_pfs_path(struct pfs_node *cur)
{
	char *temp, *path;

	temp = malloc(MAXPATHLEN, M_TEMP, M_WAITOK);
	path = malloc(MAXPATHLEN, M_TEMP, M_WAITOK);
	path[0] = '\0';

	do {
		snprintf(temp, MAXPATHLEN, "%s/%s", cur->pn_name, path);
		strlcpy(path, temp, MAXPATHLEN);
		cur = cur->pn_parent;
	} while (cur->pn_parent != NULL);

	path[strlen(path) - 1] = '\0'; /* remove extra slash */
	free(temp, M_TEMP);
	return (path);
}