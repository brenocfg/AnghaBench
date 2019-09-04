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
 int /*<<< orphan*/  DB_AGENT_KEYS ; 
 int /*<<< orphan*/  DB_AGENT_VALS ; 
 int /*<<< orphan*/  DB_GEN_STATS ; 
 int /*<<< orphan*/  DB_HOSTNAMES ; 
 int /*<<< orphan*/  DB_UNIQUE_KEYS ; 
 void* dbpath_agent_keys ; 
 void* dbpath_agent_vals ; 
 void* dbpath_general_stats ; 
 void* dbpath_hostnames ; 
 void* dbpath_unique_keys ; 
 void* get_dbname (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
set_prog_tables_dbpaths (void)
{
  dbpath_agent_keys = get_dbname (DB_AGENT_KEYS, -1);
  dbpath_agent_vals = get_dbname (DB_AGENT_VALS, -1);
  dbpath_general_stats = get_dbname (DB_GEN_STATS, -1);
  dbpath_hostnames = get_dbname (DB_HOSTNAMES, -1);
  dbpath_unique_keys = get_dbname (DB_UNIQUE_KEYS, -1);
}