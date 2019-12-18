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
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_4__ {int /*<<< orphan*/  repos_root_url; } ;
struct TYPE_5__ {TYPE_1__ loc; } ;
typedef  TYPE_2__ merge_target_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR_UNSUPPORTED_FEATURE ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  svn_dirent_local_style (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_uri__is_ancestor (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static svn_error_t *
check_repos_match(const merge_target_t *target,
                  const char *local_abspath,
                  const char *url,
                  apr_pool_t *scratch_pool)
{
  if (!svn_uri__is_ancestor(target->loc.repos_root_url, url))
    return svn_error_createf(
        SVN_ERR_UNSUPPORTED_FEATURE, NULL,
         _("URL '%s' of '%s' is not in repository '%s'"),
         url, svn_dirent_local_style(local_abspath, scratch_pool),
         target->loc.repos_root_url);

  return SVN_NO_ERROR;
}