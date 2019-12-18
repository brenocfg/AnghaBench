#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  s3stmt; int /*<<< orphan*/  needs_reset; TYPE_2__* db; } ;
typedef  TYPE_1__ svn_sqlite__stmt_t ;
struct TYPE_8__ {int /*<<< orphan*/  db3; } ;
typedef  TYPE_2__ svn_sqlite__db_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SQLITE_ERR (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 TYPE_1__* apr_palloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sqlite3_prepare_v2 (int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
prepare_statement(svn_sqlite__stmt_t **stmt, svn_sqlite__db_t *db,
                  const char *text, apr_pool_t *result_pool)
{
  *stmt = apr_palloc(result_pool, sizeof(**stmt));
  (*stmt)->db = db;
  (*stmt)->needs_reset = FALSE;

  SQLITE_ERR(sqlite3_prepare_v2(db->db3, text, -1, &(*stmt)->s3stmt, NULL), db);

  return SVN_NO_ERROR;
}