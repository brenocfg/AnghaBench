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
 int /*<<< orphan*/  err (int,char*,char const*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  log_debugx (char*,char const*) ; 
 int /*<<< orphan*/  node_expand_direct_maps (struct node*) ; 
 int /*<<< orphan*/  node_expand_includes (struct node*,int) ; 
 int /*<<< orphan*/  parse_master_yyin (struct node*,char const*) ; 
 int /*<<< orphan*/ * yyin ; 

void
parse_master(struct node *root, const char *master)
{

	log_debugx("parsing auto_master file at \"%s\"", master);

	yyin = fopen(master, "r");
	if (yyin == NULL)
		err(1, "unable to open %s", master);

	parse_master_yyin(root, master);

	fclose(yyin);
	yyin = NULL;

	log_debugx("done parsing \"%s\"", master);

	node_expand_includes(root, true);
	node_expand_direct_maps(root);
}