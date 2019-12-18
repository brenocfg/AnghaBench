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
typedef  int /*<<< orphan*/  svn_ra_session_t ;
struct TYPE_6__ {int /*<<< orphan*/  invalidate_wc_props; int /*<<< orphan*/  push_wc_prop; int /*<<< orphan*/  set_wc_prop; int /*<<< orphan*/  get_wc_prop; int /*<<< orphan*/  auth_baton; int /*<<< orphan*/  open_tmp_file; } ;
typedef  TYPE_1__ svn_ra_callbacks_t ;
struct TYPE_7__ {int /*<<< orphan*/ * progress_baton; int /*<<< orphan*/ * progress_func; int /*<<< orphan*/  invalidate_wc_props; int /*<<< orphan*/  push_wc_prop; int /*<<< orphan*/  set_wc_prop; int /*<<< orphan*/  get_wc_prop; int /*<<< orphan*/  auth_baton; int /*<<< orphan*/  open_tmp_file; } ;
typedef  TYPE_2__ svn_ra_callbacks2_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_ra_create_callbacks (TYPE_2__**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_ra_open2 (int /*<<< orphan*/ **,char const*,TYPE_2__*,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *svn_ra_open(svn_ra_session_t **session_p,
                         const char *repos_URL,
                         const svn_ra_callbacks_t *callbacks,
                         void *callback_baton,
                         apr_hash_t *config,
                         apr_pool_t *pool)
{
  /* Deprecated function. Copy the contents of the svn_ra_callbacks_t
     to a new svn_ra_callbacks2_t and call svn_ra_open2(). */
  svn_ra_callbacks2_t *callbacks2;
  SVN_ERR(svn_ra_create_callbacks(&callbacks2, pool));
  callbacks2->open_tmp_file = callbacks->open_tmp_file;
  callbacks2->auth_baton = callbacks->auth_baton;
  callbacks2->get_wc_prop = callbacks->get_wc_prop;
  callbacks2->set_wc_prop = callbacks->set_wc_prop;
  callbacks2->push_wc_prop = callbacks->push_wc_prop;
  callbacks2->invalidate_wc_props = callbacks->invalidate_wc_props;
  callbacks2->progress_func = NULL;
  callbacks2->progress_baton = NULL;
  return svn_ra_open2(session_p, repos_URL,
                      callbacks2, callback_baton,
                      config, pool);
}