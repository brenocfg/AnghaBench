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
struct agent_table {int agents_num; struct agent** agents; } ;
struct agent {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE_IN (void (*) (struct agent_table*,struct agent*)) ; 
 int /*<<< orphan*/  TRACE_OUT (void (*) (struct agent_table*,struct agent*)) ; 
 int /*<<< orphan*/  agent_cmp_func ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct agent**) ; 
 struct agent** malloc (int) ; 
 int /*<<< orphan*/  memcpy (struct agent**,struct agent**,int) ; 
 int /*<<< orphan*/  qsort (struct agent**,size_t,int,int /*<<< orphan*/ ) ; 

void
register_agent(struct agent_table *at, struct agent *a)
{
	struct agent **new_agents;
    	size_t new_agents_num;

	TRACE_IN(register_agent);
	assert(at != NULL);
	assert(a != NULL);
	new_agents_num = at->agents_num + 1;
	new_agents = malloc(sizeof(*new_agents) *
		new_agents_num);
	assert(new_agents != NULL);
	memcpy(new_agents, at->agents, at->agents_num * sizeof(struct agent *));
	new_agents[new_agents_num - 1] = a;
	qsort(new_agents, new_agents_num, sizeof(struct agent *),
		agent_cmp_func);

	free(at->agents);
	at->agents = new_agents;
	at->agents_num = new_agents_num;
    	TRACE_OUT(register_agent);
}