#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int len; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ svn_stringbuf_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  readline_symlink (void*,TYPE_1__**,char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strncmp (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  svn_stringbuf_remove (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static svn_error_t *
readline_symlink_git(void *baton, svn_stringbuf_t **line, const char **eol_str,
                     svn_boolean_t *eof, apr_pool_t *result_pool,
                     apr_pool_t *scratch_pool)
{
  SVN_ERR(readline_symlink(baton, line, eol_str, eof,
                           result_pool, scratch_pool));

  if (*line && (*line)->len > 5 && !strncmp((*line)->data, "link ", 5))
    svn_stringbuf_remove(*line, 0, 5); /* Skip "link " */

  return SVN_NO_ERROR;
}