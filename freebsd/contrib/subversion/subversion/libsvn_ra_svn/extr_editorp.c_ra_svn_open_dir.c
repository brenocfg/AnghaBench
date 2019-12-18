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
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_2__ {int /*<<< orphan*/  eb; int /*<<< orphan*/  conn; int /*<<< orphan*/  token; } ;
typedef  TYPE_1__ ra_svn_baton_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  check_for_error (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * make_token (char,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* ra_svn_make_baton (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_svn__write_cmd_open_dir (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *ra_svn_open_dir(const char *path, void *parent_baton,
                                    svn_revnum_t rev, apr_pool_t *pool,
                                    void **child_baton)
{
  ra_svn_baton_t *b = parent_baton;
  svn_string_t *token = make_token('d', b->eb, pool);

  SVN_ERR(check_for_error(b->eb, pool));
  SVN_ERR(svn_ra_svn__write_cmd_open_dir(b->conn, pool, path, b->token,
                                         token, rev));
  *child_baton = ra_svn_make_baton(b->conn, pool, b->eb, token);
  return SVN_NO_ERROR;
}