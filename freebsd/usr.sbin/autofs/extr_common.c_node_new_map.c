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
struct node {char* n_key; char* n_options; char* n_map; char const* n_config_file; int n_config_line; int /*<<< orphan*/  n_children; struct node* n_parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 struct node* calloc (int,int) ; 
 int /*<<< orphan*/  log_err (int,char*) ; 
 int /*<<< orphan*/  n_next ; 
 char* strdup (char*) ; 

struct node *
node_new_map(struct node *parent, char *key, char *options, char *map,
    const char *config_file, int config_line)
{
	struct node *n;

	n = calloc(1, sizeof(*n));
	if (n == NULL)
		log_err(1, "calloc");

	TAILQ_INIT(&n->n_children);
	assert(key != NULL);
	assert(key[0] != '\0');
	n->n_key = key;
	if (options != NULL)
		n->n_options = options;
	else
		n->n_options = strdup("");
	n->n_map = map;
	assert(config_file != NULL);
	n->n_config_file = config_file;
	assert(config_line >= 0);
	n->n_config_line = config_line;

	assert(parent != NULL);
	n->n_parent = parent;
	TAILQ_INSERT_TAIL(&parent->n_children, n, n_next);

	return (n);
}