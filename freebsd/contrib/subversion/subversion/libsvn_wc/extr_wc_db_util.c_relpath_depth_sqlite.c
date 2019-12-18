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
typedef  int /*<<< orphan*/  svn_sqlite__value_t ;
typedef  int /*<<< orphan*/  svn_sqlite__context_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int apr_int64_t ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 scalar_t__ SVN_SQLITE__TEXT ; 
 int /*<<< orphan*/  svn_sqlite__result_int64 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  svn_sqlite__result_null (int /*<<< orphan*/ *) ; 
 char* svn_sqlite__value_text (int /*<<< orphan*/ *) ; 
 scalar_t__ svn_sqlite__value_type (int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
relpath_depth_sqlite(svn_sqlite__context_t *sctx,
                     int argc,
                     svn_sqlite__value_t *values[],
                     void *baton)
{
  const char *path = NULL;
  apr_int64_t depth;

  if (argc == 1 && svn_sqlite__value_type(values[0]) == SVN_SQLITE__TEXT)
    path = svn_sqlite__value_text(values[0]);
  if (!path)
    {
      svn_sqlite__result_null(sctx);
      return SVN_NO_ERROR;
    }

  depth = *path ? 1 : 0;
  while (*path)
    {
      if (*path == '/')
        ++depth;
      ++path;
    }
  svn_sqlite__result_int64(sctx, depth);

  return SVN_NO_ERROR;
}