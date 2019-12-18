#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ svn_string_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct file_baton {int /*<<< orphan*/  ood_changed_date; TYPE_1__* dir_baton; int /*<<< orphan*/  ood_changed_author; int /*<<< orphan*/  ood_changed_rev; int /*<<< orphan*/  prop_changed; } ;
typedef  int /*<<< orphan*/  apr_time_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_4__ {int /*<<< orphan*/  pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_PROP_ENTRY_COMMITTED_DATE ; 
 int /*<<< orphan*/  SVN_PROP_ENTRY_COMMITTED_REV ; 
 int /*<<< orphan*/  SVN_PROP_ENTRY_LAST_AUTHOR ; 
 int /*<<< orphan*/  SVN_STR_TO_REV (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  apr_pstrdup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_time_from_cstring (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ svn_wc_is_normal_prop (char const*) ; 

__attribute__((used)) static svn_error_t *
change_file_prop(void *file_baton,
                 const char *name,
                 const svn_string_t *value,
                 apr_pool_t *pool)
{
  struct file_baton *fb = file_baton;
  if (svn_wc_is_normal_prop(name))
    fb->prop_changed = TRUE;

  /* Note any changes to the repository. */
  if (value != NULL)
    {
      if (strcmp(name, SVN_PROP_ENTRY_COMMITTED_REV) == 0)
        fb->ood_changed_rev = SVN_STR_TO_REV(value->data);
      else if (strcmp(name, SVN_PROP_ENTRY_LAST_AUTHOR) == 0)
        fb->ood_changed_author = apr_pstrdup(fb->dir_baton->pool,
                                              value->data);
      else if (strcmp(name, SVN_PROP_ENTRY_COMMITTED_DATE) == 0)
        {
          apr_time_t tm;
          SVN_ERR(svn_time_from_cstring(&tm, value->data,
                                        fb->dir_baton->pool));
          fb->ood_changed_date = tm;
        }
    }

  return SVN_NO_ERROR;
}