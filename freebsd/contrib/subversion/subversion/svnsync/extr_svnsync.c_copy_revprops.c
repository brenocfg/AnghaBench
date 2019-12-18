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
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  log_properties_copied (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  remove_props_not_in_source (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_rev_proplist (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svnsync_normalize_revprops (int /*<<< orphan*/ *,int*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_revprops (int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
copy_revprops(svn_ra_session_t *from_session,
              svn_ra_session_t *to_session,
              svn_revnum_t rev,
              svn_boolean_t sync,
              svn_boolean_t skip_unchanged,
              svn_boolean_t quiet,
              const char *source_prop_encoding,
              int *normalized_count,
              apr_pool_t *pool)
{
  apr_pool_t *subpool = svn_pool_create(pool);
  apr_hash_t *existing_props, *rev_props;
  int filtered_count = 0;

  /* Get the list of revision properties on REV of TARGET. We're only interested
     in the property names, but we'll get the values 'for free'. */
  if (sync)
    SVN_ERR(svn_ra_rev_proplist(to_session, rev, &existing_props, subpool));
  else
    existing_props = NULL;

  /* Get the list of revision properties on REV of SOURCE. */
  SVN_ERR(svn_ra_rev_proplist(from_session, rev, &rev_props, subpool));

  /* If necessary, normalize encoding and line ending style and return the count
     of EOL-normalized properties in int *NORMALIZED_COUNT. */
  SVN_ERR(svnsync_normalize_revprops(rev_props, normalized_count,
                                     source_prop_encoding, pool));

  /* Copy all but the svn:svnsync properties. */
  SVN_ERR(write_revprops(&filtered_count, to_session, rev, rev_props,
                         skip_unchanged ? existing_props : NULL, pool));

  /* Delete those properties that were in TARGET but not in SOURCE */
  if (sync)
    SVN_ERR(remove_props_not_in_source(to_session, rev,
                                       rev_props, existing_props, pool));

  if (! quiet)
    SVN_ERR(log_properties_copied(filtered_count > 0, rev, pool));

  svn_pool_destroy(subpool);

  return SVN_NO_ERROR;
}