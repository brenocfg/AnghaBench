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
typedef  int /*<<< orphan*/  trail_t ;
typedef  int /*<<< orphan*/  svn_fs_t ;
typedef  scalar_t__ svn_filesize_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  DBT ;
typedef  int /*<<< orphan*/  DBC ;

/* Variables and functions */
 int /*<<< orphan*/ * BDB_WRAP (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int DB_NOTFOUND ; 
 int /*<<< orphan*/  N_ (char*) ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int get_next_length (scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  locate_key (scalar_t__*,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_base__str_to_dbt (int /*<<< orphan*/ *,char const*) ; 

svn_error_t *
svn_fs_bdb__string_size(svn_filesize_t *size,
                        svn_fs_t *fs,
                        const char *key,
                        trail_t *trail,
                        apr_pool_t *pool)
{
  int db_err;
  DBT query;
  DBC *cursor;
  apr_size_t length;
  svn_filesize_t total;

  svn_fs_base__str_to_dbt(&query, key);

  SVN_ERR(locate_key(&length, &cursor, &query, fs, trail, pool));

  total = length;
  while (1)
    {
      /* Remember, if any error happens, our cursor has been closed
         for us. */
      db_err = get_next_length(&length, cursor, &query);

      /* No more records? Then return the total length. */
      if (db_err == DB_NOTFOUND)
        {
          *size = total;
          return SVN_NO_ERROR;
        }
      if (db_err)
        return BDB_WRAP(fs, N_("fetching string length"), db_err);

      total += length;
    }

  /* NOTREACHED */
}