#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ svn_string_t ;
typedef  int /*<<< orphan*/  svn_ra_serf__xml_estate_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_5__ {int /*<<< orphan*/  pool; int /*<<< orphan*/  activity_collection; } ;
typedef  TYPE_2__ options_context_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int HREF ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  svn_urlpath__canonicalize (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
options_closed(svn_ra_serf__xml_estate_t *xes,
               void *baton,
               int leaving_state,
               const svn_string_t *cdata,
               apr_hash_t *attrs,
               apr_pool_t *scratch_pool)
{
  options_context_t *opt_ctx = baton;

  SVN_ERR_ASSERT(leaving_state == HREF);
  SVN_ERR_ASSERT(cdata != NULL);

  opt_ctx->activity_collection = svn_urlpath__canonicalize(cdata->data,
                                                           opt_ctx->pool);

  return SVN_NO_ERROR;
}