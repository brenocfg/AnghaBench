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
struct status_baton {scalar_t__ text_conflicts; scalar_t__ prop_conflicts; scalar_t__ tree_conflicts; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  svn_cmdline_printf (int /*<<< orphan*/ *,char*,char*) ; 

__attribute__((used)) static svn_error_t *
print_conflict_stats(struct status_baton *sb, apr_pool_t *pool)
{
  if (sb->text_conflicts > 0 || sb->prop_conflicts > 0 ||
      sb->tree_conflicts > 0)
      SVN_ERR(svn_cmdline_printf(pool, "%s", _("Summary of conflicts:\n")));

  if (sb->text_conflicts > 0)
    SVN_ERR(svn_cmdline_printf
      (pool, _("  Text conflicts: %u\n"), sb->text_conflicts));

  if (sb->prop_conflicts > 0)
    SVN_ERR(svn_cmdline_printf
      (pool, _("  Property conflicts: %u\n"), sb->prop_conflicts));

  if (sb->tree_conflicts > 0)
    SVN_ERR(svn_cmdline_printf
      (pool, _("  Tree conflicts: %u\n"), sb->tree_conflicts));

  return SVN_NO_ERROR;
}