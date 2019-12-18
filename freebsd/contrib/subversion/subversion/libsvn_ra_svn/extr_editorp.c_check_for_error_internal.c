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
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
struct TYPE_6__ {TYPE_2__* conn; scalar_t__ got_status; } ;
typedef  TYPE_1__ ra_svn_edit_baton_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_7__ {int may_check_for_error; scalar_t__ error_check_interval; scalar_t__ written_since_error_check; } ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int) ; 
 int /*<<< orphan*/  SVN_ERR_RA_SVN_MALFORMED_DATA ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_ra_svn__data_available (TYPE_2__*,scalar_t__*) ; 
 int /*<<< orphan*/  svn_ra_svn__read_cmd_response (TYPE_2__*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  svn_ra_svn__write_cmd_abort_edit (TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
check_for_error_internal(ra_svn_edit_baton_t *eb, apr_pool_t *pool)
{
  svn_boolean_t available;
  SVN_ERR_ASSERT(!eb->got_status);

  /* reset TX counter */
  eb->conn->written_since_error_check = 0;

  /* if we weren't asked to always check, wait for at least the next TX */
  eb->conn->may_check_for_error = eb->conn->error_check_interval == 0;

  /* any incoming data? */
  SVN_ERR(svn_ra_svn__data_available(eb->conn, &available));
  if (available)
    {
      eb->got_status = TRUE;
      SVN_ERR(svn_ra_svn__write_cmd_abort_edit(eb->conn, pool));
      SVN_ERR(svn_ra_svn__read_cmd_response(eb->conn, pool, ""));
      /* We shouldn't get here if the consumer is doing its job. */
      return svn_error_create(SVN_ERR_RA_SVN_MALFORMED_DATA, NULL,
                              _("Successful edit status returned too soon"));
    }
  return SVN_NO_ERROR;
}