#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  name; scalar_t__ value; } ;
typedef  TYPE_1__ svn_prop_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  serf_bucket_t ;
typedef  int /*<<< orphan*/  serf_bucket_alloc_t ;
struct TYPE_7__ {scalar_t__ old_props; int /*<<< orphan*/  prop_changes; } ;
typedef  TYPE_2__ proppatch_context_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_index_t ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  SVN_DAV_PROP_NS_CUSTOM ; 
 int /*<<< orphan*/  SVN_DAV_PROP_NS_DAV ; 
 int /*<<< orphan*/  SVN_DAV_PROP_NS_SVN ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_VA_NULL ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/ * apr_hash_first (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * apr_hash_next (int /*<<< orphan*/ *) ; 
 TYPE_1__* apr_hash_this_val (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * serf_bucket_aggregate_create (int /*<<< orphan*/ *) ; 
 scalar_t__ svn_hash_gets (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_ra_serf__add_close_tag_buckets (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  svn_ra_serf__add_open_tag_buckets (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,char*,...) ; 
 int /*<<< orphan*/  svn_ra_serf__add_xml_header_buckets (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_prop_xml (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
create_proppatch_body(serf_bucket_t **bkt,
                      void *baton,
                      serf_bucket_alloc_t *alloc,
                      apr_pool_t *pool /* request pool */,
                      apr_pool_t *scratch_pool)
{
  proppatch_context_t *ctx = baton;
  serf_bucket_t *body_bkt;
  svn_boolean_t opened = FALSE;
  apr_hash_index_t *hi;

  body_bkt = serf_bucket_aggregate_create(alloc);

  svn_ra_serf__add_xml_header_buckets(body_bkt, alloc);
  svn_ra_serf__add_open_tag_buckets(body_bkt, alloc, "D:propertyupdate",
                                    "xmlns:D", "DAV:",
                                    "xmlns:V", SVN_DAV_PROP_NS_DAV,
                                    "xmlns:C", SVN_DAV_PROP_NS_CUSTOM,
                                    "xmlns:S", SVN_DAV_PROP_NS_SVN,
                                    SVN_VA_NULL);

  /* First we write property SETs */
  for (hi = apr_hash_first(scratch_pool, ctx->prop_changes);
       hi;
       hi = apr_hash_next(hi))
    {
      svn_prop_t *prop = apr_hash_this_val(hi);

      if (prop->value
          || (ctx->old_props && svn_hash_gets(ctx->old_props, prop->name)))
        {
          if (!opened)
            {
              opened = TRUE;
              svn_ra_serf__add_open_tag_buckets(body_bkt, alloc, "D:set",
                                                SVN_VA_NULL);
              svn_ra_serf__add_open_tag_buckets(body_bkt, alloc, "D:prop",
                                                SVN_VA_NULL);
            }

          SVN_ERR(write_prop_xml(ctx, body_bkt, alloc, prop,
                                 pool, scratch_pool));
        }
    }

  if (opened)
    {
      svn_ra_serf__add_close_tag_buckets(body_bkt, alloc, "D:prop");
      svn_ra_serf__add_close_tag_buckets(body_bkt, alloc, "D:set");
    }

  /* And then property REMOVEs */
  opened = FALSE;

  for (hi = apr_hash_first(scratch_pool, ctx->prop_changes);
       hi;
       hi = apr_hash_next(hi))
    {
      svn_prop_t *prop = apr_hash_this_val(hi);

      if (!prop->value
          && !(ctx->old_props && svn_hash_gets(ctx->old_props, prop->name)))
        {
          if (!opened)
            {
              opened = TRUE;
              svn_ra_serf__add_open_tag_buckets(body_bkt, alloc, "D:remove",
                                                SVN_VA_NULL);
              svn_ra_serf__add_open_tag_buckets(body_bkt, alloc, "D:prop",
                                                SVN_VA_NULL);
            }

          SVN_ERR(write_prop_xml(ctx, body_bkt, alloc, prop,
                                 pool, scratch_pool));
        }
    }

  if (opened)
    {
      svn_ra_serf__add_close_tag_buckets(body_bkt, alloc, "D:prop");
      svn_ra_serf__add_close_tag_buckets(body_bkt, alloc, "D:remove");
    }

  svn_ra_serf__add_close_tag_buckets(body_bkt, alloc, "D:propertyupdate");

  *bkt = body_bkt;
  return SVN_NO_ERROR;
}