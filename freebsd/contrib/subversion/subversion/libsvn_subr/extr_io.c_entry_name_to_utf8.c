#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ apr_err; } ;
typedef  TYPE_1__ svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 scalar_t__ APR_EINVAL ; 
 TYPE_1__* SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 char* apr_pstrdup (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  svn_dirent_local_style (char const*,int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_error_createf (scalar_t__,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* svn_path_cstring_to_utf8 (char const**,char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
entry_name_to_utf8(const char **name_p,
                   const char *name,
                   const char *parent,
                   apr_pool_t *pool)
{
#if defined(WIN32) || defined(DARWIN)
  *name_p = apr_pstrdup(pool, name);
  return SVN_NO_ERROR;
#else
  svn_error_t *err = svn_path_cstring_to_utf8(name_p, name, pool);
  if (err && err->apr_err == APR_EINVAL)
    {
      return svn_error_createf(err->apr_err, err,
                               _("Error converting entry "
                                 "in directory '%s' to UTF-8"),
                               svn_dirent_local_style(parent, pool));
    }
  return err;
#endif
}