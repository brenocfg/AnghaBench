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
 int DB_LOCK_DEADLOCK ; 
 int SVN_ERR_FS_BERKELEY_DB ; 
 int SVN_ERR_FS_BERKELEY_DB_DEADLOCK ; 

__attribute__((used)) static int
bdb_err_to_apr_err(int db_err)
{
  if (db_err == DB_LOCK_DEADLOCK)
    return SVN_ERR_FS_BERKELEY_DB_DEADLOCK;
  else
    return SVN_ERR_FS_BERKELEY_DB;
}