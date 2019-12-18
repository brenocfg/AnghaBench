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
 int /*<<< orphan*/  dbpath_agent_keys ; 
 int /*<<< orphan*/  dbpath_agent_vals ; 
 int /*<<< orphan*/  dbpath_general_stats ; 
 int /*<<< orphan*/  dbpath_hostnames ; 
 int /*<<< orphan*/  dbpath_unique_keys ; 
 int /*<<< orphan*/  ht_agent_keys ; 
 int /*<<< orphan*/  ht_agent_vals ; 
 int /*<<< orphan*/  ht_general_stats ; 
 int /*<<< orphan*/  ht_hostnames ; 
 int /*<<< orphan*/  ht_unique_keys ; 
 int /*<<< orphan*/  tc_db_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
free_prog_tables (void)
{
  tc_db_close (ht_agent_keys, dbpath_agent_keys);
  tc_db_close (ht_agent_vals, dbpath_agent_vals);
  tc_db_close (ht_general_stats, dbpath_general_stats);
  tc_db_close (ht_hostnames, dbpath_hostnames);
  tc_db_close (ht_unique_keys, dbpath_unique_keys);
}