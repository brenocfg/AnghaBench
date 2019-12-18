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
 int /*<<< orphan*/  SQLITE_CONFIG_LOG ; 
 int /*<<< orphan*/  sqlite3_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  sqlite_error_log ; 

void
svn_sqlite__dbg_enable_errorlog(void)
{
#if defined(SVN_DEBUG) && defined(SQLITE_CONFIG_LOG)
  sqlite3_config(SQLITE_CONFIG_LOG, sqlite_error_log, (void*)NULL /* baton */);
#endif
}