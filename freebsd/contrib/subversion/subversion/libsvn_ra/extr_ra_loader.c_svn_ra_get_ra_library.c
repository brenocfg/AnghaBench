#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  (* get_version ) () ;} ;
typedef  TYPE_1__ svn_ra_plugin_t ;
typedef  int /*<<< orphan*/  (* svn_ra_init_func_t ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct ra_lib_defn {int /*<<< orphan*/ * ra_name; int /*<<< orphan*/  (* compat_initfunc ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;int /*<<< orphan*/  schemes; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_RA_ILLEGAL_URL ; 
 int /*<<< orphan*/  SVN_RA_ABI_VERSION ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/ * apr_hash_make (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * check_ra_version (int /*<<< orphan*/ ,char const*) ; 
 char* has_scheme_of (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  load_ra_module (int /*<<< orphan*/ *,int /*<<< orphan*/  (*) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *),int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct ra_lib_defn* ra_libraries ; 
 int /*<<< orphan*/  stub1 () ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 TYPE_1__* svn_hash_gets (int /*<<< orphan*/ *,char const*) ; 

svn_error_t *
svn_ra_get_ra_library(svn_ra_plugin_t **library,
                      void *ra_baton,
                      const char *url,
                      apr_pool_t *pool)
{
  const struct ra_lib_defn *defn;
  apr_pool_t *load_pool = ra_baton;
  apr_hash_t *ht = apr_hash_make(pool);

  /* Figure out which RA library key matches URL. */
  for (defn = ra_libraries; defn->ra_name != NULL; ++defn)
    {
      const char *scheme;
      if ((scheme = has_scheme_of(defn->schemes, url)))
        {
          svn_ra_init_func_t compat_initfunc = defn->compat_initfunc;

          if (! compat_initfunc)
            {
              SVN_ERR(load_ra_module
                      (NULL, &compat_initfunc, defn->ra_name, load_pool));
            }
          if (! compat_initfunc)
            {
              continue;
            }

          SVN_ERR(compat_initfunc(SVN_RA_ABI_VERSION, load_pool, ht));

          *library = svn_hash_gets(ht, scheme);

          /* The library may support just a subset of the schemes listed,
             so we have to check here too. */
          if (! *library)
            break;

          return check_ra_version((*library)->get_version(), scheme);
        }
    }

  /* Couldn't find a match... */
  *library = NULL;
  return svn_error_createf(SVN_ERR_RA_ILLEGAL_URL, NULL,
                           _("Unrecognized URL scheme '%s'"), url);
}