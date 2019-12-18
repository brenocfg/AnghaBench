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
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_config_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  svn_config_create2 (int /*<<< orphan*/ **,scalar_t__,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_config_merge (int /*<<< orphan*/ *,char const*,scalar_t__) ; 
 int /*<<< orphan*/  svn_config_read3 (int /*<<< orphan*/ **,char const*,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
read_all(svn_config_t **cfgp,
         const char *sys_registry_path,
         const char *usr_registry_path,
         const char *sys_file_path,
         const char *usr_file_path,
         apr_pool_t *pool)
{
  svn_boolean_t red_config = FALSE;  /* "red" is the past tense of "read" */

  /*** Read system-wide configurations first... ***/

#ifdef WIN32
  if (sys_registry_path)
    {
      SVN_ERR(svn_config_read3(cfgp, sys_registry_path, FALSE, FALSE, FALSE,
                               pool));
      red_config = TRUE;
    }
#endif /* WIN32 */

  if (sys_file_path)
    {
      if (red_config)
        SVN_ERR(svn_config_merge(*cfgp, sys_file_path, FALSE));
      else
        {
          SVN_ERR(svn_config_read3(cfgp, sys_file_path,
                                   FALSE, FALSE, FALSE, pool));
          red_config = TRUE;
        }
    }

  /*** ...followed by per-user configurations. ***/

#ifdef WIN32
  if (usr_registry_path)
    {
      if (red_config)
        SVN_ERR(svn_config_merge(*cfgp, usr_registry_path, FALSE));
      else
        {
          SVN_ERR(svn_config_read3(cfgp, usr_registry_path,
                                   FALSE, FALSE, FALSE, pool));
          red_config = TRUE;
        }
    }
#endif /* WIN32 */

  if (usr_file_path)
    {
      if (red_config)
        SVN_ERR(svn_config_merge(*cfgp, usr_file_path, FALSE));
      else
        {
          SVN_ERR(svn_config_read3(cfgp, usr_file_path,
                                   FALSE, FALSE, FALSE, pool));
          red_config = TRUE;
        }
    }

  if (! red_config)
    SVN_ERR(svn_config_create2(cfgp, FALSE, FALSE, pool));

  return SVN_NO_ERROR;
}