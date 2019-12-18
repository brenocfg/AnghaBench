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
struct revision_report_t {int /*<<< orphan*/  send_deltas; int /*<<< orphan*/  low_water_mark; int /*<<< orphan*/  revision; scalar_t__ include_path; } ;
typedef  int /*<<< orphan*/  serf_bucket_t ;
typedef  int /*<<< orphan*/  serf_bucket_alloc_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_VA_NULL ; 
 int /*<<< orphan*/  SVN_XML_NAMESPACE ; 
 scalar_t__ apr_ltoa (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * serf_bucket_aggregate_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_serf__add_close_tag_buckets (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  svn_ra_serf__add_open_tag_buckets (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_ra_serf__add_tag_buckets (int /*<<< orphan*/ *,char*,scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
create_replay_body(serf_bucket_t **bkt,
                   void *baton,
                   serf_bucket_alloc_t *alloc,
                   apr_pool_t *pool /* request pool */,
                   apr_pool_t *scratch_pool)
{
  struct revision_report_t *ctx = baton;
  serf_bucket_t *body_bkt;

  body_bkt = serf_bucket_aggregate_create(alloc);

  svn_ra_serf__add_open_tag_buckets(body_bkt, alloc,
                                    "S:replay-report",
                                    "xmlns:S", SVN_XML_NAMESPACE,
                                    SVN_VA_NULL);

  /* If we have a non-NULL include path, we add it to the body and
     omit the revision; otherwise, the reverse. */
  if (ctx->include_path)
    {
      svn_ra_serf__add_tag_buckets(body_bkt,
                                   "S:include-path",
                                   ctx->include_path,
                                   alloc);
    }
  else
    {
      svn_ra_serf__add_tag_buckets(body_bkt,
                                   "S:revision",
                                   apr_ltoa(pool, ctx->revision),
                                   alloc);
    }
  svn_ra_serf__add_tag_buckets(body_bkt,
                               "S:low-water-mark",
                               apr_ltoa(pool, ctx->low_water_mark),
                               alloc);

  svn_ra_serf__add_tag_buckets(body_bkt,
                               "S:send-deltas",
                               apr_ltoa(pool, ctx->send_deltas),
                               alloc);

  svn_ra_serf__add_close_tag_buckets(body_bkt, alloc, "S:replay-report");

  *bkt = body_bkt;
  return SVN_NO_ERROR;
}