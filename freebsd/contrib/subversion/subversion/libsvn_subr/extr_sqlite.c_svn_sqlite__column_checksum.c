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
typedef  int /*<<< orphan*/  svn_sqlite__stmt_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_checksum_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  svn_checksum_deserialize (int /*<<< orphan*/  const**,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* svn_sqlite__column_text (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_sqlite__column_checksum(const svn_checksum_t **checksum,
                            svn_sqlite__stmt_t *stmt, int column,
                            apr_pool_t *result_pool)
{
  const char *digest = svn_sqlite__column_text(stmt, column, NULL);

  if (digest == NULL)
    *checksum = NULL;
  else
    SVN_ERR(svn_checksum_deserialize(checksum, digest,
                                     result_pool, result_pool));

  return SVN_NO_ERROR;
}