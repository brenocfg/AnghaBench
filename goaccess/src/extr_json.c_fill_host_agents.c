#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {size_t size; TYPE_1__* items; } ;
struct TYPE_3__ {char* agent; } ;
typedef  TYPE_2__ GAgents ;

/* Variables and functions */
 char* ht_get_host_agent_val (int) ; 

__attribute__((used)) static int
fill_host_agents (void *val, void *user_data)
{
  GAgents *agents = user_data;
  char *agent = ht_get_host_agent_val ((*(int *) val));

  if (agent == NULL)
    return 1;

  agents->items[agents->size].agent = agent;
  agents->size++;

  return 0;
}