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
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  serf_bucket_headers_setn (int /*<<< orphan*/ *,char*,char*) ; 

__attribute__((used)) static svn_error_t*
setup_getlock_headers(serf_bucket_t *headers,
                      void *baton,
                      apr_pool_t *pool /* request pool */,
                      apr_pool_t *scratch_pool)
{
  serf_bucket_headers_setn(headers, "Depth", "0");

  return SVN_NO_ERROR;
}