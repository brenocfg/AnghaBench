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
struct revision_report_t {int /*<<< orphan*/  session; } ;
typedef  int /*<<< orphan*/  serf_bucket_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  svn_ra_serf__setup_svndiff_accept_encoding (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
setup_headers(serf_bucket_t *headers,
              void *baton,
              apr_pool_t *request_pool,
              apr_pool_t *scratch_pool)
{
  struct revision_report_t *ctx = baton;

  svn_ra_serf__setup_svndiff_accept_encoding(headers, ctx->session);

  return SVN_NO_ERROR;
}