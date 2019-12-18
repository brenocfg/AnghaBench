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
typedef  int /*<<< orphan*/  serf_bucket_t ;
typedef  int /*<<< orphan*/  serf_bucket_alloc_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_VA_NULL ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int /*<<< orphan*/  svn_ra_serf__add_cdata_len_buckets (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_ra_serf__add_close_tag_buckets (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  svn_ra_serf__add_open_tag_buckets (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 

void svn_ra_serf__add_tag_buckets(serf_bucket_t *agg_bucket, const char *tag,
                                  const char *value,
                                  serf_bucket_alloc_t *bkt_alloc)
{
  svn_ra_serf__add_open_tag_buckets(agg_bucket, bkt_alloc, tag, SVN_VA_NULL);

  if (value)
    {
      svn_ra_serf__add_cdata_len_buckets(agg_bucket, bkt_alloc,
                                         value, strlen(value));
    }

  svn_ra_serf__add_close_tag_buckets(agg_bucket, bkt_alloc, tag);
}