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

__attribute__((used)) static char *
get_dbname (const char *dbname, int module)
{
  char *path = NULL;
#ifdef TCB_MEMHASH
  (void) dbname;
  (void) module;
  path = alloc_string ("*");
#endif

#ifdef TCB_BTREE
  path = tc_db_set_path (dbname, module);
#endif

  return path;
}