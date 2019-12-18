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
struct TYPE_5__ {TYPE_1__* value; } ;
typedef  TYPE_2__ svn_prop_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_cancel_func_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_array_header_t ;
struct TYPE_4__ {int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_PROP_EOL_STYLE ; 
 int /*<<< orphan*/  TRUE ; 
 char* apr_pstrdup (int /*<<< orphan*/ *,char const*) ; 
 TYPE_2__* get_prop (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_io_file_del_on_pool_cleanup ; 
 int /*<<< orphan*/  svn_io_open_unique_file3 (int /*<<< orphan*/ *,char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_subst_copy_and_translate4 (char const*,char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_subst_eol_style_from_value (int /*<<< orphan*/ *,char const**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
maybe_update_target_eols(const char **new_target_abspath,
                         const apr_array_header_t *prop_diff,
                         const char *old_target_abspath,
                         svn_cancel_func_t cancel_func,
                         void *cancel_baton,
                         apr_pool_t *result_pool,
                         apr_pool_t *scratch_pool)
{
  const svn_prop_t *prop = get_prop(prop_diff, SVN_PROP_EOL_STYLE);

  if (prop && prop->value)
    {
      const char *eol;
      const char *tmp_new;

      svn_subst_eol_style_from_value(NULL, &eol, prop->value->data);
      SVN_ERR(svn_io_open_unique_file3(NULL, &tmp_new, NULL,
                                       svn_io_file_del_on_pool_cleanup,
                                       result_pool, scratch_pool));

      /* Always 'repair' EOLs here, so that we can apply a diff that
         changes from inconsistent newlines and no 'svn:eol-style' to
         consistent newlines and 'svn:eol-style' set.  */
      SVN_ERR(svn_subst_copy_and_translate4(old_target_abspath,
                                            tmp_new,
                                            eol,
                                            TRUE /* repair */,
                                            NULL /* keywords */,
                                            FALSE /* expand */,
                                            FALSE /* special */,
                                            cancel_func, cancel_baton,
                                            scratch_pool));
      *new_target_abspath = apr_pstrdup(result_pool, tmp_new);
    }
  else
    *new_target_abspath = apr_pstrdup(result_pool, old_target_abspath);

  return SVN_NO_ERROR;
}