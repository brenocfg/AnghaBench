#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_ra_svn__list_t ;
struct TYPE_4__ {int /*<<< orphan*/  expiration_date; int /*<<< orphan*/  creation_date; int /*<<< orphan*/  path; int /*<<< orphan*/  comment; int /*<<< orphan*/  owner; int /*<<< orphan*/  token; } ;
typedef  TYPE_1__ svn_lock_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  svn_fspath__canonicalize (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_lock_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_svn__parse_tuple (int /*<<< orphan*/  const*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const**,char const**) ; 
 int /*<<< orphan*/  svn_time_from_cstring (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *parse_lock(const svn_ra_svn__list_t *list,
                               apr_pool_t *pool,
                               svn_lock_t **lock)
{
  const char *cdate, *edate;
  *lock = svn_lock_create(pool);
  SVN_ERR(svn_ra_svn__parse_tuple(list, "ccc(?c)c(?c)", &(*lock)->path,
                                  &(*lock)->token, &(*lock)->owner,
                                  &(*lock)->comment, &cdate, &edate));
  (*lock)->path = svn_fspath__canonicalize((*lock)->path, pool);
  SVN_ERR(svn_time_from_cstring(&(*lock)->creation_date, cdate, pool));
  if (edate)
    SVN_ERR(svn_time_from_cstring(&(*lock)->expiration_date, edate, pool));
  return SVN_NO_ERROR;
}