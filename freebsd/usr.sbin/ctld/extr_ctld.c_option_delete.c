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
struct options {int dummy; } ;
struct option {struct option* o_value; struct option* o_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_REMOVE (struct options*,struct option*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct option*) ; 
 int /*<<< orphan*/  o_next ; 

void
option_delete(struct options *options, struct option *o)
{

	TAILQ_REMOVE(options, o, o_next);
	free(o->o_name);
	free(o->o_value);
	free(o);
}