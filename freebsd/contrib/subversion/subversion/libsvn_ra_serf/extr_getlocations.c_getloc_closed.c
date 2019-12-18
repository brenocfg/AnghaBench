#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_string_t ;
typedef  scalar_t__ svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_ra_serf__xml_estate_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  rev ;
struct TYPE_2__ {int /*<<< orphan*/  pool; int /*<<< orphan*/  paths; } ;
typedef  TYPE_1__ loc_context_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  scalar_t__ apr_int64_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int LOCATION ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  apr_hash_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apr_pmemdup (int /*<<< orphan*/ ,scalar_t__*,int) ; 
 int /*<<< orphan*/  apr_pstrdup (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  svn_cstring_atoi64 (scalar_t__*,char const*) ; 
 char* svn_hash_gets (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static svn_error_t *
getloc_closed(svn_ra_serf__xml_estate_t *xes,
              void *baton,
              int leaving_state,
              const svn_string_t *cdata,
              apr_hash_t *attrs,
              apr_pool_t *scratch_pool)
{
  loc_context_t *loc_ctx = baton;
  const char *revstr;
  const char *path;

  SVN_ERR_ASSERT(leaving_state == LOCATION);

  revstr = svn_hash_gets(attrs, "rev");
  path = svn_hash_gets(attrs, "path");
  if (revstr != NULL && path != NULL)
    {
      apr_int64_t rev_val;
      svn_revnum_t rev;

      SVN_ERR(svn_cstring_atoi64(&rev_val, revstr));
      rev = (svn_revnum_t)rev_val;

      apr_hash_set(loc_ctx->paths,
                   apr_pmemdup(loc_ctx->pool, &rev, sizeof(rev)), sizeof(rev),
                   apr_pstrdup(loc_ctx->pool, path));
    }

  return SVN_NO_ERROR;
}