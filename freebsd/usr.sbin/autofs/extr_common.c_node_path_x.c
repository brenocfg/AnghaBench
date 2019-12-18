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
struct node {char* n_key; struct node* n_parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 char* concat (char*,char,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ node_is_direct_key (struct node const*) ; 

__attribute__((used)) static char *
node_path_x(const struct node *n, char *x)
{
	char *path;

	if (n->n_parent == NULL)
		return (x);

	/*
	 * Return "/-" for direct maps only if we were asked for path
	 * to the "/-" node itself, not to any of its subnodes.
	 */
	if (node_is_direct_key(n) && x[0] != '\0')
		return (x);

	assert(n->n_key[0] != '\0');
	path = concat(n->n_key, '/', x);
	free(x);

	return (node_path_x(n->n_parent, path));
}