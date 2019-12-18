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
struct node {int /*<<< orphan*/  n_children; void* n_options; void* n_key; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 struct node* calloc (int,int) ; 
 void* checked_strdup (char*) ; 
 int /*<<< orphan*/  log_err (int,char*) ; 

struct node *
node_new_root(void)
{
	struct node *n;

	n = calloc(1, sizeof(*n));
	if (n == NULL)
		log_err(1, "calloc");
	// XXX
	n->n_key = checked_strdup("/");
	n->n_options = checked_strdup("");

	TAILQ_INIT(&n->n_children);

	return (n);
}