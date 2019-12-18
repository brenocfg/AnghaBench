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
struct cfparams {int dummy; } ;
struct cfparam {struct cfparam* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_REMOVE (struct cfparams*,struct cfparam*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct cfparam*) ; 
 int /*<<< orphan*/  free_param_strings (struct cfparam*) ; 
 int /*<<< orphan*/  tq ; 

__attribute__((used)) static void
free_param(struct cfparams *pp, struct cfparam *p)
{
	free(p->name);
	free_param_strings(p);
	TAILQ_REMOVE(pp, p, tq);
	free(p);
}