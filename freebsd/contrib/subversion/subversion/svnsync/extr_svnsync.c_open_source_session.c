#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ svn_string_t ;
typedef  int /*<<< orphan*/  svn_ra_session_t ;
typedef  int /*<<< orphan*/  svn_ra_callbacks2_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_EINVAL ; 
 int /*<<< orphan*/  SVNSYNC_PROP_FROM_URL ; 
 int /*<<< orphan*/  SVNSYNC_PROP_FROM_UUID ; 
 int /*<<< orphan*/  SVNSYNC_PROP_LAST_MERGED_REV ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* svn_hash_gets (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_opt__arg_canonicalize_url (char const**,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_open4 (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_rev_proplist (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
open_source_session(svn_ra_session_t **from_session,
                    svn_string_t **last_merged_rev,
                    const char *from_url,
                    svn_ra_session_t *to_session,
                    svn_ra_callbacks2_t *callbacks,
                    apr_hash_t *config,
                    void *baton,
                    apr_pool_t *pool)
{
  apr_hash_t *props;
  svn_string_t *from_url_str, *from_uuid_str;

  SVN_ERR(svn_ra_rev_proplist(to_session, 0, &props, pool));

  from_url_str = svn_hash_gets(props, SVNSYNC_PROP_FROM_URL);
  from_uuid_str = svn_hash_gets(props, SVNSYNC_PROP_FROM_UUID);
  *last_merged_rev = svn_hash_gets(props, SVNSYNC_PROP_LAST_MERGED_REV);

  if (! from_url_str || ! from_uuid_str || ! *last_merged_rev)
    return svn_error_create
      (APR_EINVAL, NULL,
       _("Destination repository has not been initialized"));

  /* ### TODO: Should we validate that FROM_URL_STR->data matches any
     provided FROM_URL here?  */
  if (! from_url)
    SVN_ERR(svn_opt__arg_canonicalize_url(&from_url, from_url_str->data,
                                          pool));

  /* Open the session to copy the revision data. */
  SVN_ERR(svn_ra_open4(from_session, NULL, from_url, from_uuid_str->data,
                       callbacks, baton, config, pool));

  return SVN_NO_ERROR;
}