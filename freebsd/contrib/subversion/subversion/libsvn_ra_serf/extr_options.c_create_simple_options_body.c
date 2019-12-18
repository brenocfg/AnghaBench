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
 int /*<<< orphan*/ * SERF_BUCKET_SIMPLE_STRING (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  serf_bucket_aggregate_append (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * serf_bucket_aggregate_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_serf__add_xml_header_buckets (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
create_simple_options_body(serf_bucket_t **body_bkt,
                           void *baton,
                           serf_bucket_alloc_t *alloc,
                           apr_pool_t *pool /* request pool */,
                           apr_pool_t *scratch_pool)
{
  serf_bucket_t *body;
  serf_bucket_t *s;

  body = serf_bucket_aggregate_create(alloc);
  svn_ra_serf__add_xml_header_buckets(body, alloc);

  s = SERF_BUCKET_SIMPLE_STRING("<D:options xmlns:D=\"DAV:\" />", alloc);
  serf_bucket_aggregate_append(body, s);

  *body_bkt = body;
  return SVN_NO_ERROR;
}