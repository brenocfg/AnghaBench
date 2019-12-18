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
typedef  int /*<<< orphan*/  svn_ra_serf__session_t ;
typedef  int /*<<< orphan*/  svn_ra_serf__handler_t ;
typedef  int /*<<< orphan*/  svn_ra_serf__dav_props_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/ * apr_hash_make (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  deliver_node_props ; 
 int /*<<< orphan*/  svn_ra_serf__context_run_one (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_serf__create_propfind_handler (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_ra_serf__fetch_node_props(apr_hash_t **results,
                              svn_ra_serf__session_t *session,
                              const char *url,
                              svn_revnum_t revision,
                              const svn_ra_serf__dav_props_t *which_props,
                              apr_pool_t *result_pool,
                              apr_pool_t *scratch_pool)
{
  apr_hash_t *props;
  svn_ra_serf__handler_t *handler;

  props = apr_hash_make(result_pool);

  SVN_ERR(svn_ra_serf__create_propfind_handler(&handler, session,
                                               url, revision, "0", which_props,
                                               deliver_node_props,
                                               props, scratch_pool));

  SVN_ERR(svn_ra_serf__context_run_one(handler, scratch_pool));

  *results = props;
  return SVN_NO_ERROR;
}