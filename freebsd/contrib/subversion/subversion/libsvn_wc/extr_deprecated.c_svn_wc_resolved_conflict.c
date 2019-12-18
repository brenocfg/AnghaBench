#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  svn_wc_notify_func_t ;
typedef  int /*<<< orphan*/  svn_wc_adm_access_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct compat_notify_baton_t {void* baton; int /*<<< orphan*/  func; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  compat_call_notify_func ; 
 int /*<<< orphan*/ * svn_wc_resolved_conflict2 (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct compat_notify_baton_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_wc_resolved_conflict(const char *path,
                         svn_wc_adm_access_t *adm_access,
                         svn_boolean_t resolve_text,
                         svn_boolean_t resolve_props,
                         svn_boolean_t recurse,
                         svn_wc_notify_func_t notify_func,
                         void *notify_baton,
                         apr_pool_t *pool)
{
  struct compat_notify_baton_t nb;

  nb.func = notify_func;
  nb.baton = notify_baton;

  return svn_wc_resolved_conflict2(path, adm_access,
                                   resolve_text, resolve_props, recurse,
                                   compat_call_notify_func, &nb,
                                   NULL, NULL, pool);

}