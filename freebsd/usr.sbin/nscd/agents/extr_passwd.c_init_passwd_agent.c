#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  type; int /*<<< orphan*/ * name; } ;
struct common_agent {int /*<<< orphan*/  lookup_func; TYPE_1__ parent; } ;
struct agent {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMMON_AGENT ; 
 int /*<<< orphan*/  TRACE_IN (struct agent* (*) ()) ; 
 int /*<<< orphan*/  TRACE_OUT (struct agent* (*) ()) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 struct common_agent* calloc (int,int) ; 
 int /*<<< orphan*/  passwd_lookup_func ; 
 int /*<<< orphan*/ * strdup (char*) ; 

struct agent *
init_passwd_agent(void)
{
	struct common_agent	*retval;

	TRACE_IN(init_passwd_agent);
	retval = calloc(1, sizeof(*retval));
	assert(retval != NULL);

	retval->parent.name = strdup("passwd");
	assert(retval->parent.name != NULL);

	retval->parent.type = COMMON_AGENT;
	retval->lookup_func = passwd_lookup_func;

	TRACE_OUT(init_passwd_agent);
	return ((struct agent *)retval);
}