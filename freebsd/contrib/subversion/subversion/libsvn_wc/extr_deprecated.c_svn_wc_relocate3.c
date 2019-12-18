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
typedef  int /*<<< orphan*/  svn_wc_relocation_validator3_t ;
typedef  int /*<<< orphan*/  svn_wc_context_t ;
typedef  int /*<<< orphan*/  svn_wc_adm_access_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_UNSUPPORTED_FEATURE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  svn_dirent_get_absolute (char const**,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_wc__adm_get_db (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__context_create_with_db (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc_context_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc_relocate4 (int /*<<< orphan*/ *,char const*,char const*,char const*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_wc_relocate3(const char *path,
                 svn_wc_adm_access_t *adm_access,
                 const char *from,
                 const char *to,
                 svn_boolean_t recurse,
                 svn_wc_relocation_validator3_t validator,
                 void *validator_baton,
                 apr_pool_t *pool)
{
  const char *local_abspath;
  svn_wc_context_t *wc_ctx;

  if (! recurse)
    SVN_ERR(svn_error_create(SVN_ERR_UNSUPPORTED_FEATURE, NULL,
                             _("Non-recursive relocation not supported")));

  SVN_ERR(svn_dirent_get_absolute(&local_abspath, path, pool));
  SVN_ERR(svn_wc__context_create_with_db(&wc_ctx, NULL /* config */,
                                         svn_wc__adm_get_db(adm_access),
                                         pool));

  SVN_ERR(svn_wc_relocate4(wc_ctx, local_abspath, from, to,
                           validator, validator_baton, pool));

  return svn_error_trace(svn_wc_context_destroy(wc_ctx));
}