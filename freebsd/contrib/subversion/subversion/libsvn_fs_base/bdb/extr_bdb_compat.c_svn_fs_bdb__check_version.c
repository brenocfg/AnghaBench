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
 int DB_OLD_VERSION ; 
 int DB_VERSION_MAJOR ; 
 int DB_VERSION_MINOR ; 
 int /*<<< orphan*/  db_version (int*,int*,int /*<<< orphan*/ *) ; 

int
svn_fs_bdb__check_version(void)
{
  int major, minor;

  db_version(&major, &minor, NULL);
  if (major != DB_VERSION_MAJOR || minor != DB_VERSION_MINOR)
    return DB_OLD_VERSION;
  return 0;
}