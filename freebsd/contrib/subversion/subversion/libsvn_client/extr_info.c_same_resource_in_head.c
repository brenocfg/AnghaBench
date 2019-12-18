#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_ra_session_t ;
struct TYPE_11__ {int /*<<< orphan*/  number; } ;
struct TYPE_12__ {TYPE_1__ value; int /*<<< orphan*/  kind; } ;
typedef  TYPE_2__ svn_opt_revision_t ;
struct TYPE_13__ {scalar_t__ apr_err; } ;
typedef  TYPE_3__ svn_error_t ;
typedef  int /*<<< orphan*/  svn_client_ctx_t ;
typedef  int svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  SVN_ERR (TYPE_3__*) ; 
 scalar_t__ SVN_ERR_CLIENT_UNRELATED_RESOURCES ; 
 scalar_t__ SVN_ERR_FS_NOT_FOUND ; 
 TYPE_3__* SVN_NO_ERROR ; 
 scalar_t__ strcmp (char const*,char const*) ; 
 TYPE_3__* svn_client__repos_locations (char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,TYPE_2__*,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_3__*) ; 
 int /*<<< orphan*/  svn_opt_revision_head ; 
 int /*<<< orphan*/  svn_opt_revision_number ; 

__attribute__((used)) static svn_error_t *
same_resource_in_head(svn_boolean_t *same_p,
                      const char *url,
                      svn_revnum_t rev,
                      svn_ra_session_t *ra_session,
                      svn_client_ctx_t *ctx,
                      apr_pool_t *pool)
{
  svn_error_t *err;
  svn_opt_revision_t operative_rev, peg_rev;
  const char *head_url;

  peg_rev.kind = svn_opt_revision_head;
  operative_rev.kind = svn_opt_revision_number;
  operative_rev.value.number = rev;

  err = svn_client__repos_locations(&head_url, NULL, NULL, NULL,
                                    ra_session,
                                    url, &peg_rev,
                                    &operative_rev, NULL,
                                    ctx, pool);
  if (err &&
      ((err->apr_err == SVN_ERR_CLIENT_UNRELATED_RESOURCES) ||
       (err->apr_err == SVN_ERR_FS_NOT_FOUND)))
    {
      svn_error_clear(err);
      *same_p = FALSE;
      return SVN_NO_ERROR;
    }
  else
    SVN_ERR(err);

  /* ### Currently, the URLs should always be equal, since we can't
     ### walk forwards in history. */
  *same_p = (strcmp(url, head_url) == 0);

  return SVN_NO_ERROR;
}