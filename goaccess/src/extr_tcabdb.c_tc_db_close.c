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
struct TYPE_2__ {int /*<<< orphan*/  keep_db_files; } ;
typedef  int /*<<< orphan*/  TCADB ;

/* Variables and functions */
 int /*<<< orphan*/  FATAL (char*,char*) ; 
 int /*<<< orphan*/  LOG_DEBUG (char*) ; 
 TYPE_1__ conf ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  tcadbclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcadbdel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcremovelink (char*) ; 

__attribute__((used)) static int
tc_db_close (TCADB * adb, char *dbname)
{
  if (adb == NULL)
    return 1;

  /* close the database */
  if (!tcadbclose (adb))
    FATAL ("Unable to close DB: %s", dbname);

  /* delete the object */
  tcadbdel (adb);

#ifdef TCB_BTREE
  /* remove database file */
  if (!conf.keep_db_files && !tcremovelink (dbname))
    LOG_DEBUG (("Unable to remove DB: %s\n", dbname));
#endif
  free (dbname);

  return 0;
}