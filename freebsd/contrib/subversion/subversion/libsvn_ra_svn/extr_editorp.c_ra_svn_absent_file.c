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
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_2__ {int /*<<< orphan*/  token; int /*<<< orphan*/  conn; int /*<<< orphan*/  eb; } ;
typedef  TYPE_1__ ra_svn_baton_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_RA_SVN_CAP_ABSENT_ENTRIES ; 
 int /*<<< orphan*/  check_for_error (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_svn__write_cmd_absent_file (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_ra_svn_has_capability (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *ra_svn_absent_file(const char *path,
                                       void *parent_baton, apr_pool_t *pool)
{
  ra_svn_baton_t *b = parent_baton;

  /* Avoid sending an unknown command if the other end doesn't support
     absent-file. */
  if (! svn_ra_svn_has_capability(b->conn, SVN_RA_SVN_CAP_ABSENT_ENTRIES))
    return SVN_NO_ERROR;

  SVN_ERR(check_for_error(b->eb, pool));
  SVN_ERR(svn_ra_svn__write_cmd_absent_file(b->conn, pool, path, b->token));
  return SVN_NO_ERROR;
}