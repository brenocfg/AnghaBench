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
struct TYPE_5__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ svn_string_t ;
typedef  int /*<<< orphan*/  svn_stream_t ;
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_repos_t ;
typedef  int /*<<< orphan*/  svn_repos_authz_func_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_time_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_PROP_REVISION_DATE ; 
 int /*<<< orphan*/ * apr_hash_make (int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_hash_gets (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_hash_sets (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  svn_repos__dump_revision_record (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_repos_fs_revision_proplist (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_string_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_time_from_cstring (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_time_to_cstring (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
write_revision_record(svn_stream_t *stream,
                      svn_repos_t *repos,
                      svn_revnum_t rev,
                      svn_boolean_t include_revprops,
                      svn_repos_authz_func_t authz_func,
                      void *authz_baton,
                      apr_pool_t *pool)
{
  apr_hash_t *props;
  apr_time_t timetemp;
  svn_string_t *datevalue;

  if (include_revprops)
    {
      SVN_ERR(svn_repos_fs_revision_proplist(&props, repos, rev,
                                             authz_func, authz_baton, pool));

      /* Run revision date properties through the time conversion to
        canonicalize them. */
      /* ### Remove this when it is no longer needed for sure. */
      datevalue = svn_hash_gets(props, SVN_PROP_REVISION_DATE);
      if (datevalue)
        {
          SVN_ERR(svn_time_from_cstring(&timetemp, datevalue->data, pool));
          datevalue = svn_string_create(svn_time_to_cstring(timetemp, pool),
                                        pool);
          svn_hash_sets(props, SVN_PROP_REVISION_DATE, datevalue);
        }
    }
   else
    {
      /* Although we won't use it, we still need this container for the
         call below. */
      props = apr_hash_make(pool);
    }

  SVN_ERR(svn_repos__dump_revision_record(stream, rev, NULL, props,
                                          include_revprops,
                                          pool));
  return SVN_NO_ERROR;
}