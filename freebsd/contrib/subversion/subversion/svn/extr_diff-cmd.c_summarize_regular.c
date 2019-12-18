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
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_3__ {scalar_t__ summarize_kind; scalar_t__ prop_changed; int /*<<< orphan*/  path; } ;
typedef  TYPE_1__ svn_client_diff_summarize_t ;
struct summarize_baton_t {char* anchor; scalar_t__ ignore_properties; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  kind_to_char (scalar_t__) ; 
 int /*<<< orphan*/  stdout ; 
 scalar_t__ svn_client_diff_summarize_kind_normal ; 
 int /*<<< orphan*/ * svn_cmdline_fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_cmdline_printf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char,char const*) ; 
 char* svn_dirent_join (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* svn_dirent_local_style (char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_path_is_url (char const*) ; 
 char* svn_path_url_add_component2 (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
summarize_regular(const svn_client_diff_summarize_t *summary,
                  void *baton,
                  apr_pool_t *pool)
{
  struct summarize_baton_t *b = baton;
  const char *path = b->anchor;
  char prop_change;

  if (b->ignore_properties &&
      summary->summarize_kind == svn_client_diff_summarize_kind_normal)
    return SVN_NO_ERROR;

  /* Tack on the target path, so we can differentiate between different parts
   * of the output when we're given multiple targets. */
  if (svn_path_is_url(path))
    {
      path = svn_path_url_add_component2(path, summary->path, pool);
    }
  else
    {
      path = svn_dirent_join(path, summary->path, pool);

      /* Convert non-urls to local style, so that things like ""
         show up as "." */
      path = svn_dirent_local_style(path, pool);
    }

  /* Note: This output format tries to look like the output of 'svn status',
   *       thus the blank spaces where information that is not relevant to
   *       a diff summary would go. */

  prop_change = summary->prop_changed ? 'M' : ' ';
  if (b->ignore_properties)
    prop_change = ' ';

  SVN_ERR(svn_cmdline_printf(pool, "%c%c      %s\n",
                             kind_to_char(summary->summarize_kind),
                             prop_change, path));

  return svn_cmdline_fflush(stdout);
}