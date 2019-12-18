#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_string_t ;
typedef  int /*<<< orphan*/  svn_revnum_t ;
struct TYPE_6__ {TYPE_1__* vtable; } ;
typedef  TYPE_2__ svn_ra_session_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_5__ {int /*<<< orphan*/ * (* rev_prop ) (TYPE_2__*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_IS_VALID_REVNUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * stub1 (TYPE_2__*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 

svn_error_t *svn_ra_rev_prop(svn_ra_session_t *session,
                             svn_revnum_t rev,
                             const char *name,
                             svn_string_t **value,
                             apr_pool_t *pool)
{
  SVN_ERR_ASSERT(SVN_IS_VALID_REVNUM(rev));
  return session->vtable->rev_prop(session, rev, name, value, pool);
}