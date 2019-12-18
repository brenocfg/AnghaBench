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
typedef  int /*<<< orphan*/  svn_delta_editor_t ;
typedef  int /*<<< orphan*/  svn_commit_callback_t ;
typedef  int /*<<< orphan*/  svn_commit_callback2_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
struct TYPE_2__ {int /*<<< orphan*/ * (* get_commit_editor ) (void*,int /*<<< orphan*/  const**,void**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  APR_HASH_KEY_STRING ; 
 int /*<<< orphan*/  SVN_PROP_REVISION_LOG ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_1__ VTBL ; 
 int /*<<< orphan*/ * apr_hash_make (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_hash_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * stub1 (void*,int /*<<< orphan*/  const**,void**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_compat_wrap_commit_callback (int /*<<< orphan*/ *,void**,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_string_create (char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *compat_get_commit_editor(void *session_baton,
                                             const svn_delta_editor_t
                                             **editor,
                                             void **edit_baton,
                                             const char *log_msg,
                                             svn_commit_callback_t callback,
                                             void *callback_baton,
                                             apr_pool_t *pool)
{
  svn_commit_callback2_t callback2;
  void *callback2_baton;
  apr_hash_t *revprop_table = apr_hash_make(pool);

  svn_compat_wrap_commit_callback(&callback2, &callback2_baton,
                                  callback, callback_baton,
                                  pool);
  apr_hash_set(revprop_table, SVN_PROP_REVISION_LOG, APR_HASH_KEY_STRING,
               svn_string_create(log_msg, pool));
  return VTBL.get_commit_editor(session_baton, editor, edit_baton,
                                revprop_table, callback2, callback2_baton,
                                NULL, TRUE, pool);
}