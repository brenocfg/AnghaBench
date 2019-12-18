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

/* Variables and functions */
 int /*<<< orphan*/  HOSTS ; 
 int /*<<< orphan*/  MTRC_AGENTS ; 
 int /*<<< orphan*/  free_agent_values ; 
 void* get_hash (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tc_db_foreach (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
free_agent_list (void)
{
  void *hash = get_hash (HOSTS, MTRC_AGENTS);
  if (!hash)
    return;

  tc_db_foreach (hash, free_agent_values, NULL);
}