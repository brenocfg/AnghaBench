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
typedef  scalar_t__ svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_ra_serf__xml_estate_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_5__ {scalar_t__* revision_deleted; } ;
typedef  TYPE_2__ drev_context_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  scalar_t__ apr_int64_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int VERSION_NAME ; 
 int /*<<< orphan*/  svn_cstring_atoi64 (scalar_t__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
getdrev_closed(svn_ra_serf__xml_estate_t *xes,
               void *baton,
               int leaving_state,
               const svn_string_t *cdata,
               apr_hash_t *attrs,
               apr_pool_t *scratch_pool)
{
  drev_context_t *drev_ctx = baton;
  apr_int64_t rev;

  SVN_ERR_ASSERT(leaving_state == VERSION_NAME);
  SVN_ERR_ASSERT(cdata != NULL);

  SVN_ERR(svn_cstring_atoi64(&rev, cdata->data));
  *drev_ctx->revision_deleted = (svn_revnum_t)rev;

  return SVN_NO_ERROR;
}