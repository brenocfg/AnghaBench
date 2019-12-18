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
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  serf_bucket_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_DAV_VTXN_NAME_HEADER ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  serf_bucket_headers_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_uuid_generate (int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
setup_post_headers(serf_bucket_t *headers,
                   void *baton,
                   apr_pool_t *pool /* request pool */,
                   apr_pool_t *scratch_pool)
{
#ifdef SVN_DAV_SEND_VTXN_NAME
  /* Enable this to exercise the VTXN-NAME code based on a client
     supplied transaction name. */
  serf_bucket_headers_set(headers, SVN_DAV_VTXN_NAME_HEADER,
                          svn_uuid_generate(pool));
#endif

  return SVN_NO_ERROR;
}