#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ svn_string_t ;
typedef  scalar_t__ svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_ra_session_t ;
struct TYPE_16__ {scalar_t__ apr_err; } ;
typedef  TYPE_2__ svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct TYPE_17__ {char const* from_url; int /*<<< orphan*/  source_prop_encoding; int /*<<< orphan*/  quiet; int /*<<< orphan*/  config; int /*<<< orphan*/  source_callbacks; int /*<<< orphan*/  allow_non_empty; } ;
typedef  TYPE_3__ subcommand_baton_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_EINVAL ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVNSYNC_PROP_FROM_URL ; 
 int /*<<< orphan*/  SVNSYNC_PROP_FROM_UUID ; 
 int /*<<< orphan*/  SVNSYNC_PROP_LAST_MERGED_REV ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_RA_PARTIAL_REPLAY_NOT_SUPPORTED ; 
 scalar_t__ SVN_ERR_UNKNOWN_CAPABILITY ; 
 TYPE_2__* SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_RA_CAPABILITY_PARTIAL_REPLAY ; 
 int /*<<< orphan*/ * _ (char*) ; 
 int /*<<< orphan*/  copy_revprops (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_properties_normalized (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char const*,char const*) ; 
 TYPE_2__* svn_error_create (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *) ; 
 TYPE_2__* svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_2__* svn_error_trace (TYPE_2__*) ; 
 int /*<<< orphan*/  svn_ra_change_rev_prop2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_get_latest_revnum (int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_get_repos_root2 (int /*<<< orphan*/ *,char const**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_get_uuid2 (int /*<<< orphan*/ *,char const**,int /*<<< orphan*/ *) ; 
 TYPE_2__* svn_ra_has_capability (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_open4 (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_rev_prop (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_string_create (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_string_createf (int /*<<< orphan*/ *,char*,scalar_t__) ; 

__attribute__((used)) static svn_error_t *
do_initialize(svn_ra_session_t *to_session,
              subcommand_baton_t *baton,
              apr_pool_t *pool)
{
  svn_ra_session_t *from_session;
  svn_string_t *from_url;
  svn_revnum_t latest, from_latest;
  const char *uuid, *root_url;
  int normalized_rev_props_count;

  /* First, sanity check to see that we're copying into a brand new
     repos.  If we aren't, and we aren't being asked to forcibly
     complete this initialization, that's a bad news.  */
  SVN_ERR(svn_ra_get_latest_revnum(to_session, &latest, pool));
  if ((latest != 0) && (! baton->allow_non_empty))
    return svn_error_create
      (APR_EINVAL, NULL,
       _("Destination repository already contains revision history; consider "
         "using --allow-non-empty if the repository's revisions are known "
         "to mirror their respective revisions in the source repository"));

  SVN_ERR(svn_ra_rev_prop(to_session, 0, SVNSYNC_PROP_FROM_URL,
                          &from_url, pool));
  if (from_url && (! baton->allow_non_empty))
    return svn_error_createf
      (APR_EINVAL, NULL,
       _("Destination repository is already synchronizing from '%s'"),
       from_url->data);

  /* Now fill in our bookkeeping info in the dest repository. */

  SVN_ERR(svn_ra_open4(&from_session, NULL, baton->from_url, NULL,
                       &(baton->source_callbacks), baton,
                       baton->config, pool));
  SVN_ERR(svn_ra_get_repos_root2(from_session, &root_url, pool));

  /* If we're doing a partial replay, we have to check first if the server
     supports this. */
  if (strcmp(root_url, baton->from_url) != 0)
    {
      svn_boolean_t server_supports_partial_replay;
      svn_error_t *err = svn_ra_has_capability(from_session,
                                               &server_supports_partial_replay,
                                               SVN_RA_CAPABILITY_PARTIAL_REPLAY,
                                               pool);
      if (err && err->apr_err != SVN_ERR_UNKNOWN_CAPABILITY)
        return svn_error_trace(err);

      if (err || !server_supports_partial_replay)
        return svn_error_create(SVN_ERR_RA_PARTIAL_REPLAY_NOT_SUPPORTED, err,
                                NULL);
    }

  /* If we're initializing a non-empty destination, we'll make sure
     that it at least doesn't have more revisions than the source. */
  if (latest != 0)
    {
      SVN_ERR(svn_ra_get_latest_revnum(from_session, &from_latest, pool));
      if (from_latest < latest)
        return svn_error_create
          (APR_EINVAL, NULL,
           _("Destination repository has more revisions than source "
             "repository"));
    }

  SVN_ERR(svn_ra_change_rev_prop2(to_session, 0, SVNSYNC_PROP_FROM_URL, NULL,
                                  svn_string_create(baton->from_url, pool),
                                  pool));

  SVN_ERR(svn_ra_get_uuid2(from_session, &uuid, pool));
  SVN_ERR(svn_ra_change_rev_prop2(to_session, 0, SVNSYNC_PROP_FROM_UUID, NULL,
                                  svn_string_create(uuid, pool), pool));

  SVN_ERR(svn_ra_change_rev_prop2(to_session, 0, SVNSYNC_PROP_LAST_MERGED_REV,
                                  NULL, svn_string_createf(pool, "%ld", latest),
                                  pool));

  /* Copy all non-svnsync revprops from the LATEST rev in the source
     repository into the destination, notifying about normalized
     props, if any.  When LATEST is 0, this serves the practical
     purpose of initializing data that would otherwise be overlooked
     by the sync process (which is going to begin with r1).  When
     LATEST is not 0, this really serves merely aesthetic and
     informational purposes, keeping the output of this command
     consistent while allowing folks to see what the latest revision is.  */
  SVN_ERR(copy_revprops(from_session, to_session, latest, FALSE, FALSE,
                        baton->quiet, baton->source_prop_encoding,
                        &normalized_rev_props_count, pool));

  SVN_ERR(log_properties_normalized(normalized_rev_props_count, 0, pool));

  /* TODO: It would be nice if we could set the dest repos UUID to be
     equal to the UUID of the source repos, at least optionally.  That
     way people could check out/log/diff using a local fast mirror,
     but switch --relocate to the actual final repository in order to
     make changes...  But at this time, the RA layer doesn't have a
     way to set a UUID. */

  return SVN_NO_ERROR;
}