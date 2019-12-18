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
struct TYPE_2__ {int /*<<< orphan*/ * name; int /*<<< orphan*/  type; } ;
struct multipart_agent {TYPE_1__ parent; int /*<<< orphan*/  mp_destroy_func; int /*<<< orphan*/  mp_lookup_func; int /*<<< orphan*/  mp_init_func; } ;
struct agent {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MULTIPART_AGENT ; 
 int /*<<< orphan*/  TRACE_IN (struct agent* (*) ()) ; 
 int /*<<< orphan*/  TRACE_OUT (struct agent* (*) ()) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 struct multipart_agent* calloc (int,int) ; 
 int /*<<< orphan*/  group_mp_destroy_func ; 
 int /*<<< orphan*/  group_mp_init_func ; 
 int /*<<< orphan*/  group_mp_lookup_func ; 
 int /*<<< orphan*/ * strdup (char*) ; 

struct agent *
init_group_mp_agent(void)
{
	struct multipart_agent	*retval;

	TRACE_IN(init_group_mp_agent);
	retval = calloc(1,
		sizeof(*retval));
	assert(retval != NULL);

	retval->parent.name = strdup("group");
	retval->parent.type = MULTIPART_AGENT;
	retval->mp_init_func = group_mp_init_func;
	retval->mp_lookup_func = group_mp_lookup_func;
	retval->mp_destroy_func = group_mp_destroy_func;
	assert(retval->parent.name != NULL);

	TRACE_OUT(init_group_mp_agent);
	return ((struct agent *)retval);
}