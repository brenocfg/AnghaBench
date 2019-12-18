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
typedef  int /*<<< orphan*/  svn_cancel_func_t ;
struct compat_notify_baton_t {void* baton; int /*<<< orphan*/  func; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  compat_call_notify_func ; 
 int /*<<< orphan*/ * svn_wc_copy2 (char const*,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,struct compat_notify_baton_t*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_wc_copy(const char *src_path,
            svn_wc_adm_access_t *dst_parent,
            const char *dst_basename,
            svn_cancel_func_t cancel_func,
            void *cancel_baton,
            svn_wc_notify_func_t notify_func,
            void *notify_baton,
            apr_pool_t *pool)
{
  struct compat_notify_baton_t nb;

  nb.func = notify_func;
  nb.baton = notify_baton;

  return svn_wc_copy2(src_path, dst_parent, dst_basename, cancel_func,
                      cancel_baton, compat_call_notify_func,
                      &nb, pool);
}