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
typedef  int /*<<< orphan*/  svn_string_t ;
typedef  int /*<<< orphan*/  svn_stream_t ;
typedef  int /*<<< orphan*/  svn_ra_session_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct getter_baton {int /*<<< orphan*/  base_revision_for_url; int /*<<< orphan*/ * ra_session; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_PROP_MIME_TYPE ; 
 int /*<<< orphan*/ * svn_hash_gets (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_ra_get_file (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
get_file_for_validation(const svn_string_t **mime_type,
                        svn_stream_t *stream,
                        void *baton,
                        apr_pool_t *pool)
{
  struct getter_baton *gb = baton;
  svn_ra_session_t *ra_session = gb->ra_session;
  apr_hash_t *props;

  SVN_ERR(svn_ra_get_file(ra_session, "", gb->base_revision_for_url,
                          stream, NULL,
                          (mime_type ? &props : NULL),
                          pool));

  if (mime_type)
    *mime_type = svn_hash_gets(props, SVN_PROP_MIME_TYPE);

  return SVN_NO_ERROR;
}