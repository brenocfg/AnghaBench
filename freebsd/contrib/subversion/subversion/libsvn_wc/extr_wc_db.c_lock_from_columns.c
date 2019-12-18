#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  date; void* comment; void* owner; void* token; } ;
typedef  TYPE_1__ svn_wc__db_lock_t ;
typedef  int /*<<< orphan*/  svn_sqlite__stmt_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 TYPE_1__* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  svn_sqlite__column_int64 (int /*<<< orphan*/ *,int) ; 
 scalar_t__ svn_sqlite__column_is_null (int /*<<< orphan*/ *,int) ; 
 void* svn_sqlite__column_text (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_wc__db_lock_t *
lock_from_columns(svn_sqlite__stmt_t *stmt,
                  int col_token,
                  int col_owner,
                  int col_comment,
                  int col_date,
                  apr_pool_t *result_pool)
{
  svn_wc__db_lock_t *lock;

  if (svn_sqlite__column_is_null(stmt, col_token))
    {
      lock = NULL;
    }
  else
    {
      lock = apr_pcalloc(result_pool, sizeof(svn_wc__db_lock_t));
      lock->token = svn_sqlite__column_text(stmt, col_token, result_pool);
      lock->owner = svn_sqlite__column_text(stmt, col_owner, result_pool);
      lock->comment = svn_sqlite__column_text(stmt, col_comment, result_pool);
      lock->date = svn_sqlite__column_int64(stmt, col_date);
    }
  return lock;
}