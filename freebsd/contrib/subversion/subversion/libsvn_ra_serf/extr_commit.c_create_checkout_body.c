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
typedef  int /*<<< orphan*/  serf_bucket_alloc_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_VA_NULL ; 
 int /*<<< orphan*/ * serf_bucket_aggregate_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int /*<<< orphan*/  svn_ra_serf__add_cdata_len_buckets (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_ra_serf__add_close_tag_buckets (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  svn_ra_serf__add_empty_tag_buckets (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_ra_serf__add_open_tag_buckets (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,char*,...) ; 
 int /*<<< orphan*/  svn_ra_serf__add_xml_header_buckets (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
create_checkout_body(serf_bucket_t **bkt,
                     void *baton,
                     serf_bucket_alloc_t *alloc,
                     apr_pool_t *pool /* request pool */,
                     apr_pool_t *scratch_pool)
{
  const char *activity_url = baton;
  serf_bucket_t *body_bkt;

  body_bkt = serf_bucket_aggregate_create(alloc);

  svn_ra_serf__add_xml_header_buckets(body_bkt, alloc);
  svn_ra_serf__add_open_tag_buckets(body_bkt, alloc, "D:checkout",
                                    "xmlns:D", "DAV:",
                                    SVN_VA_NULL);
  svn_ra_serf__add_open_tag_buckets(body_bkt, alloc, "D:activity-set",
                                    SVN_VA_NULL);
  svn_ra_serf__add_open_tag_buckets(body_bkt, alloc, "D:href",
                                    SVN_VA_NULL);

  SVN_ERR_ASSERT(activity_url != NULL);
  svn_ra_serf__add_cdata_len_buckets(body_bkt, alloc,
                                     activity_url,
                                     strlen(activity_url));

  svn_ra_serf__add_close_tag_buckets(body_bkt, alloc, "D:href");
  svn_ra_serf__add_close_tag_buckets(body_bkt, alloc, "D:activity-set");
  svn_ra_serf__add_empty_tag_buckets(body_bkt, alloc,
                                     "D:apply-to-version", SVN_VA_NULL);
  svn_ra_serf__add_close_tag_buckets(body_bkt, alloc, "D:checkout");

  *bkt = body_bkt;
  return SVN_NO_ERROR;
}