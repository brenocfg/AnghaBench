#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  hook_path; } ;
typedef  TYPE_1__ svn_repos_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_REPOS__HOOK_DESC_EXT ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  apr_psprintf (int /*<<< orphan*/ *,char*,char const*,int /*<<< orphan*/ ) ; 
 char* hook_template_text (char const*,char const*,char const*,int /*<<< orphan*/ *) ; 
 char* svn_dirent_join (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_file_create (char const*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_set_file_executable (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
write_hook_template_file(svn_repos_t *repos, const char *script_name,
                         const char *description,
                         const char *script,
                         apr_pool_t *pool)
{
  const char *template_path
    = svn_dirent_join(repos->hook_path,
                      apr_psprintf(pool, "%s%s",
                                   script_name, SVN_REPOS__HOOK_DESC_EXT),
                      pool);
  const char *contents
    = hook_template_text(script_name, description, script, pool);

  SVN_ERR(svn_io_file_create(template_path, contents, pool));
  SVN_ERR(svn_io_set_file_executable(template_path, TRUE, FALSE, pool));
  return SVN_NO_ERROR;
}