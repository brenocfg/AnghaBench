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
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 char* apr_pstrdup (int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ sqlite3_column_text (int /*<<< orphan*/ ,int) ; 

const char *
svn_sqlite__column_text(svn_sqlite__stmt_t *stmt, int column,
                        apr_pool_t *result_pool)
{
  /* cast from 'unsigned char' to regular 'char'  */
  const char *result = (const char *)sqlite3_column_text(stmt->s3stmt, column);

  if (result_pool && result != NULL)
    result = apr_pstrdup(result_pool, result);

  return result;
}