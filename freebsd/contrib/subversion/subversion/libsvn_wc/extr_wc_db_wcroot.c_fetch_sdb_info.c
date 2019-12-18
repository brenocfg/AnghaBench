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
typedef  int /*<<< orphan*/  svn_sqlite__db_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int apr_int64_t ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_SQLITE__WITH_LOCK4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_sqlite__read_schema_version (int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_util_fetch_wc_id (int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  verify_stats_table (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
fetch_sdb_info(apr_int64_t *wc_id,
               int *format,
               svn_sqlite__db_t *sdb,
               apr_pool_t *scratch_pool)
{
  *wc_id = -1;
  *format = -1;

  SVN_SQLITE__WITH_LOCK4(
        svn_wc__db_util_fetch_wc_id(wc_id, sdb, scratch_pool),
        svn_sqlite__read_schema_version(format, sdb, scratch_pool),
        verify_stats_table(sdb, *format, scratch_pool),
        SVN_NO_ERROR,
        sdb);

  return SVN_NO_ERROR;
}