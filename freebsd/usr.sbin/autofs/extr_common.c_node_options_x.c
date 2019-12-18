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
struct node {struct node* n_parent; int /*<<< orphan*/  n_options; } ;

/* Variables and functions */
 char* concat (char*,char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 

__attribute__((used)) static char *
node_options_x(const struct node *n, char *x)
{
	char *options;

	if (n == NULL)
		return (x);

	options = concat(x, ',', n->n_options);
	free(x);

	return (node_options_x(n->n_parent, options));
}