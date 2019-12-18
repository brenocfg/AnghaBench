#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {TYPE_1__* vtable; int /*<<< orphan*/ * pool; int /*<<< orphan*/  cancel_baton; int /*<<< orphan*/  cancel_func; } ;
typedef  TYPE_2__ svn_ra_session_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_11__ {int /*<<< orphan*/  (* set_svn_ra_open ) (TYPE_2__*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* dup_session ) (TYPE_2__*,TYPE_2__*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 TYPE_2__* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,TYPE_2__*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_ra_get_path_relative_to_root (TYPE_2__*,char const**,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_get_session_url (TYPE_2__*,char const**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_open4 ; 

svn_error_t *
svn_ra__dup_session(svn_ra_session_t **new_session,
                    svn_ra_session_t *old_session,
                    const char *session_url,
                    apr_pool_t *result_pool,
                    apr_pool_t *scratch_pool)
{
  svn_ra_session_t *session;

  if (session_url)
    {
      const char *dummy;

      /* This verifies in new_session_url is in the repository */
      SVN_ERR(svn_ra_get_path_relative_to_root(old_session,
                                               &dummy,
                                               session_url,
                                               scratch_pool));
    }
  else
    SVN_ERR(svn_ra_get_session_url(old_session, &session_url, scratch_pool));

  /* Create the session object. */
  session = apr_pcalloc(result_pool, sizeof(*session));
  session->cancel_func = old_session->cancel_func;
  session->cancel_baton = old_session->cancel_baton;
  session->vtable = old_session->vtable;
  session->pool = result_pool;

  SVN_ERR(old_session->vtable->dup_session(session,
                                           old_session,
                                           session_url,
                                           result_pool,
                                           scratch_pool));

  if (session->vtable->set_svn_ra_open)
    SVN_ERR(session->vtable->set_svn_ra_open(session, svn_ra_open4));

  *new_session = session;
  return SVN_NO_ERROR;
}