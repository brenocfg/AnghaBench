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
struct expression {struct expression* prev; struct expression* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  exit (int) ; 
 struct expression* malloc (int) ; 
 int /*<<< orphan*/  memset (struct expression*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static struct expression *
alloc_and_hook_expr(struct expression **exp_p, struct expression **last_p)
{
	struct expression *ex, *at;

	ex = malloc(sizeof(struct expression));
	if (ex == NULL) {
		printf("Out of memory in exp allocation\n");
		exit(-2);
	}
	memset(ex, 0, sizeof(struct expression));
	if (*exp_p == NULL) {
		*exp_p = ex;
	}
	at = *last_p;
	if (at == NULL) {
		/* First one, its last */
		*last_p = ex;
	} else {
		/* Chain it to the end and update last */
		at->next = ex;
		ex->prev = at;
		*last_p = ex;
	}
	return (ex);
}