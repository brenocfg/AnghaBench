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
typedef  int /*<<< orphan*/  svn_stringbuf_t ;
struct TYPE_4__ {char** (* get_schemes ) (int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* get_description ) (int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* get_version ) () ;} ;
typedef  TYPE_1__ svn_ra__vtable_t ;
typedef  int /*<<< orphan*/  (* svn_ra__init_func_t ) (int /*<<< orphan*/ ,TYPE_1__ const**,int /*<<< orphan*/ *) ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct ra_lib_defn {int /*<<< orphan*/ * ra_name; int /*<<< orphan*/  (* initfunc ) (int /*<<< orphan*/ ,TYPE_1__ const**,int /*<<< orphan*/ *) ;} ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 char* apr_psprintf (int /*<<< orphan*/ *,char*,char const* const,...) ; 
 int /*<<< orphan*/  check_ra_version (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  load_ra_module (int /*<<< orphan*/  (*) (int /*<<< orphan*/ ,TYPE_1__ const**,int /*<<< orphan*/ *),int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct ra_lib_defn* ra_libraries ; 
 int /*<<< orphan*/  stub1 () ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *) ; 
 char** stub3 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_version () ; 
 int /*<<< orphan*/  svn_stringbuf_appendcstr (int /*<<< orphan*/ *,char*) ; 

svn_error_t *
svn_ra_print_modules(svn_stringbuf_t *output,
                     apr_pool_t *pool)
{
  const struct ra_lib_defn *defn;
  const char * const *schemes;
  svn_ra__init_func_t initfunc;
  const svn_ra__vtable_t *vtable;
  apr_pool_t *iterpool = svn_pool_create(pool);

  for (defn = ra_libraries; defn->ra_name != NULL; ++defn)
    {
      char *line;

      svn_pool_clear(iterpool);

      initfunc = defn->initfunc;
      if (! initfunc)
        SVN_ERR(load_ra_module(&initfunc, NULL, defn->ra_name,
                               iterpool));

      if (initfunc)
        {
          SVN_ERR(initfunc(svn_ra_version(), &vtable, iterpool));

          SVN_ERR(check_ra_version(vtable->get_version(), defn->ra_name));

          /* Note: if you change the formatting of the description,
             bear in mind that ra_svn's description has multiple lines when
             built with SASL. */
          line = apr_psprintf(iterpool, "* ra_%s : %s\n",
                              defn->ra_name,
                              vtable->get_description(iterpool));
          svn_stringbuf_appendcstr(output, line);

          for (schemes = vtable->get_schemes(iterpool); *schemes != NULL;
               ++schemes)
            {
              line = apr_psprintf(iterpool, _("  - handles '%s' scheme\n"),
                                  *schemes);
              svn_stringbuf_appendcstr(output, line);
            }
        }
    }

  svn_pool_destroy(iterpool);

  return SVN_NO_ERROR;
}