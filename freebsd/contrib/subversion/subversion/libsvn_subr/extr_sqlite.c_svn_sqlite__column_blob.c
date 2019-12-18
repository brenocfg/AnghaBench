#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  s3stmt; } ;
typedef  TYPE_1__ svn_sqlite__stmt_t ;
typedef  int /*<<< orphan*/  apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 void* apr_pmemdup (int /*<<< orphan*/ *,void const*,int /*<<< orphan*/ ) ; 
 void* sqlite3_column_blob (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sqlite3_column_bytes (int /*<<< orphan*/ ,int) ; 

const void *
svn_sqlite__column_blob(svn_sqlite__stmt_t *stmt, int column,
                        apr_size_t *len, apr_pool_t *result_pool)
{
  const void *val = sqlite3_column_blob(stmt->s3stmt, column);
  *len = sqlite3_column_bytes(stmt->s3stmt, column);

  if (result_pool && val != NULL)
    val = apr_pmemdup(result_pool, val, *len);

  return val;
}