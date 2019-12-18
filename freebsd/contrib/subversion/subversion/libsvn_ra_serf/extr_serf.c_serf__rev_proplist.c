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
typedef  int /*<<< orphan*/  svn_revnum_t ;
struct TYPE_7__ {TYPE_2__* priv; } ;
typedef  TYPE_1__ svn_ra_session_t ;
struct TYPE_8__ {int /*<<< orphan*/  rev_stub; } ;
typedef  TYPE_2__ svn_ra_serf__session_t ;
typedef  int /*<<< orphan*/  svn_ra_serf__handler_t ;
typedef  int /*<<< orphan*/  svn_ra_serf__dav_props_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_INVALID_REVNUM ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 scalar_t__ SVN_RA_SERF__HAVE_HTTPV2_SUPPORT (TYPE_2__*) ; 
 int /*<<< orphan*/ * apr_hash_make (int /*<<< orphan*/ *) ; 
 char* apr_psprintf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_ra_serf__context_run_one (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_serf__create_propfind_handler (int /*<<< orphan*/ **,TYPE_2__*,char const*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_serf__deliver_svn_props ; 
 int /*<<< orphan*/  svn_ra_serf__discover_vcc (char const**,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_serf__keep_only_regular_props (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
serf__rev_proplist(svn_ra_session_t *ra_session,
                   svn_revnum_t rev,
                   const svn_ra_serf__dav_props_t *fetch_props,
                   apr_hash_t **ret_props,
                   apr_pool_t *result_pool,
                   apr_pool_t *scratch_pool)
{
  svn_ra_serf__session_t *session = ra_session->priv;
  apr_hash_t *props;
  const char *propfind_path;
  svn_ra_serf__handler_t *handler;

  if (SVN_RA_SERF__HAVE_HTTPV2_SUPPORT(session))
    {
      propfind_path = apr_psprintf(scratch_pool, "%s/%ld", session->rev_stub,
                                   rev);

      /* svn_ra_serf__retrieve_props() wants to added the revision as
         a Label to the PROPFIND, which isn't really necessary when
         querying a rev-stub URI.  *Shrug*  Probably okay to leave the
         Label, but whatever. */
      rev = SVN_INVALID_REVNUM;
    }
  else
    {
      /* Use the VCC as the propfind target path. */
      SVN_ERR(svn_ra_serf__discover_vcc(&propfind_path, session,
                                        scratch_pool));
    }

  props = apr_hash_make(result_pool);
  SVN_ERR(svn_ra_serf__create_propfind_handler(&handler, session,
                                               propfind_path, rev, "0",
                                               fetch_props,
                                               svn_ra_serf__deliver_svn_props,
                                               props,
                                               scratch_pool));

  SVN_ERR(svn_ra_serf__context_run_one(handler, scratch_pool));

  svn_ra_serf__keep_only_regular_props(props, scratch_pool);

  *ret_props = props;

  return SVN_NO_ERROR;
}