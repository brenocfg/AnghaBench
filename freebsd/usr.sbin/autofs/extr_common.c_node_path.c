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
struct node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  checked_strdup (char*) ; 
 char* node_path_x (struct node const*,int /*<<< orphan*/ ) ; 
 size_t strlen (char*) ; 

char *
node_path(const struct node *n)
{
	char *path;
	size_t len;

	path = node_path_x(n, checked_strdup(""));

	/*
	 * Strip trailing slash, unless the whole path is "/".
	 */
	len = strlen(path);
	if (len > 1 && path[len - 1] == '/')
		path[len - 1] = '\0';

	return (path);
}