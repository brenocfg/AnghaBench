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
typedef  int /*<<< orphan*/  svn_client_status_t ;
struct status_baton {int /*<<< orphan*/  ctx; int /*<<< orphan*/  tree_conflicts; int /*<<< orphan*/  prop_conflicts; int /*<<< orphan*/  text_conflicts; int /*<<< orphan*/  repos_locks; int /*<<< orphan*/  skip_unrecognized; int /*<<< orphan*/  show_last_committed; int /*<<< orphan*/  detailed; int /*<<< orphan*/  suppress_externals_placeholders; int /*<<< orphan*/  target_path; int /*<<< orphan*/  target_abspath; scalar_t__ xml_mode; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * svn_cl__print_status (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_cl__print_status_xml (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
print_status_normal_or_xml(void *baton,
                           const char *path,
                           const svn_client_status_t *status,
                           apr_pool_t *pool)
{
  struct status_baton *sb = baton;

  if (sb->xml_mode)
    return svn_cl__print_status_xml(sb->target_abspath, sb->target_path,
                                    path, status, sb->ctx, pool);
  else
    return svn_cl__print_status(sb->target_abspath, sb->target_path,
                                path, status,
                                sb->suppress_externals_placeholders,
                                sb->detailed,
                                sb->show_last_committed,
                                sb->skip_unrecognized,
                                sb->repos_locks,
                                &sb->text_conflicts,
                                &sb->prop_conflicts,
                                &sb->tree_conflicts,
                                sb->ctx,
                                pool);
}