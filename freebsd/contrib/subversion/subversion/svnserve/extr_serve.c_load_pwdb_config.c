#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_repos__config_pool_t ;
struct TYPE_10__ {scalar_t__ apr_err; } ;
typedef  TYPE_1__ svn_error_t ;
typedef  int /*<<< orphan*/  svn_config_t ;
struct TYPE_11__ {int /*<<< orphan*/  repos; int /*<<< orphan*/ * pwdb; int /*<<< orphan*/  base; } ;
typedef  TYPE_2__ repository_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_STATUS_IS_EACCES (scalar_t__) ; 
 int /*<<< orphan*/  SVN_CONFIG_OPTION_PASSWORD_DB ; 
 int /*<<< orphan*/  SVN_CONFIG_SECTION_GENERAL ; 
 int /*<<< orphan*/  SVN_ERR_AUTHN_FAILED ; 
 scalar_t__ SVN_ERR_BAD_FILENAME ; 
 TYPE_1__* SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  svn_config_get (int /*<<< orphan*/ *,char const**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* svn_dirent_internal_style (char const*,int /*<<< orphan*/ *) ; 
 char* svn_dirent_join (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_1__*) ; 
 TYPE_1__* svn_error_create (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_repos__config_pool_get (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
load_pwdb_config(repository_t *repository,
                 svn_config_t *cfg,
                 svn_repos__config_pool_t *config_pool,
                 apr_pool_t *pool)
{
  const char *pwdb_path;
  svn_error_t *err;

  svn_config_get(cfg, &pwdb_path,
                 SVN_CONFIG_SECTION_GENERAL,
                 SVN_CONFIG_OPTION_PASSWORD_DB, NULL);

  repository->pwdb = NULL;
  if (pwdb_path)
    {
      pwdb_path = svn_dirent_internal_style(pwdb_path, pool);
      pwdb_path = svn_dirent_join(repository->base, pwdb_path, pool);

      err = svn_repos__config_pool_get(&repository->pwdb, config_pool,
                                       pwdb_path, TRUE,
                                       repository->repos, pool);
      if (err)
        {
          /* Because it may be possible to read the pwdb file with some
             access methods and not others, ignore errors reading the pwdb
             file and just don't present password authentication as an
             option.  Also, some authentications (e.g. --tunnel) can
             proceed without it anyway.

             ### Not entirely sure why SVN_ERR_BAD_FILENAME is checked
             ### for here.  That seems to have been introduced in r856914,
             ### and only in r870942 was the APR_EACCES check introduced. */
          if (err->apr_err != SVN_ERR_BAD_FILENAME
              && ! APR_STATUS_IS_EACCES(err->apr_err))
            {
              return svn_error_create(SVN_ERR_AUTHN_FAILED, err, NULL);
            }
          else
            /* Ignore SVN_ERR_BAD_FILENAME and APR_EACCES and proceed. */
            svn_error_clear(err);
        }
    }

  return SVN_NO_ERROR;
}