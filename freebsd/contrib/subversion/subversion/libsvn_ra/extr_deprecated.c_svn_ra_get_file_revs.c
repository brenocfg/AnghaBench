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
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_ra_session_t ;
typedef  int /*<<< orphan*/  svn_ra_file_rev_handler_t ;
typedef  int /*<<< orphan*/  svn_file_rev_handler_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int) ; 
 int /*<<< orphan*/  svn_compat_wrap_file_rev_handler (int /*<<< orphan*/ *,void**,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_ra_get_file_revs2 (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 

svn_error_t *svn_ra_get_file_revs(svn_ra_session_t *session,
                                  const char *path,
                                  svn_revnum_t start,
                                  svn_revnum_t end,
                                  svn_ra_file_rev_handler_t handler,
                                  void *handler_baton,
                                  apr_pool_t *pool)
{
  svn_file_rev_handler_t handler2;
  void *handler2_baton;

  SVN_ERR_ASSERT(*path != '/');

  svn_compat_wrap_file_rev_handler(&handler2, &handler2_baton,
                                   handler, handler_baton,
                                   pool);

  return svn_ra_get_file_revs2(session, path, start, end, FALSE, handler2,
                               handler2_baton, pool);
}