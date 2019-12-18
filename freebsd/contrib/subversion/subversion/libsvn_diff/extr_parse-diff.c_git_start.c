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
struct TYPE_3__ {int /*<<< orphan*/  operation; int /*<<< orphan*/  new_filename; int /*<<< orphan*/  old_filename; } ;
typedef  TYPE_1__ svn_patch_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int ptrdiff_t ;
typedef  enum parse_state { ____Placeholder_parse_state } parse_state ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int STRLEN_LITERAL (char*) ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  grab_filename (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int state_git_diff_seen ; 
 int state_start ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strncmp (char const*,char const*,int) ; 
 void* strstr (char const*,char*) ; 
 int /*<<< orphan*/  svn_diff_op_modified ; 

__attribute__((used)) static svn_error_t *
git_start(enum parse_state *new_state, char *line, svn_patch_t *patch,
          apr_pool_t *result_pool, apr_pool_t *scratch_pool)
{
  const char *old_path_start;
  char *old_path_end;
  const char *new_path_start;
  const char *new_path_end;
  char *new_path_marker;
  const char *old_path_marker;

  /* ### Add handling of escaped paths
   * http://www.kernel.org/pub/software/scm/git/docs/git-diff.html:
   *
   * TAB, LF, double quote and backslash characters in pathnames are
   * represented as \t, \n, \" and \\, respectively. If there is need for
   * such substitution then the whole pathname is put in double quotes.
   */

  /* Our line should look like this: 'diff --git a/path b/path'.
   *
   * If we find any deviations from that format, we return with state reset
   * to start.
   */
  old_path_marker = strstr(line, " a/");

  if (! old_path_marker)
    {
      *new_state = state_start;
      return SVN_NO_ERROR;
    }

  if (! *(old_path_marker + 3))
    {
      *new_state = state_start;
      return SVN_NO_ERROR;
    }

  new_path_marker = strstr(old_path_marker, " b/");

  if (! new_path_marker)
    {
      *new_state = state_start;
      return SVN_NO_ERROR;
    }

  if (! *(new_path_marker + 3))
    {
      *new_state = state_start;
      return SVN_NO_ERROR;
    }

  /* By now, we know that we have a line on the form '--git diff a/.+ b/.+'
   * We only need the filenames when we have deleted or added empty
   * files. In those cases the old_path and new_path is identical on the
   * 'diff --git' line.  For all other cases we fetch the filenames from
   * other header lines. */
  old_path_start = line + STRLEN_LITERAL("diff --git a/");
  new_path_end = line + strlen(line);
  new_path_start = old_path_start;

  while (TRUE)
    {
      ptrdiff_t len_old;
      ptrdiff_t len_new;

      new_path_marker = strstr(new_path_start, " b/");

      /* No new path marker, bail out. */
      if (! new_path_marker)
        break;

      old_path_end = new_path_marker;
      new_path_start = new_path_marker + STRLEN_LITERAL(" b/");

      /* No path after the marker. */
      if (! *new_path_start)
        break;

      len_old = old_path_end - old_path_start;
      len_new = new_path_end - new_path_start;

      /* Are the paths before and after the " b/" marker the same? */
      if (len_old == len_new
          && ! strncmp(old_path_start, new_path_start, len_old))
        {
          *old_path_end = '\0';
          SVN_ERR(grab_filename(&patch->old_filename, old_path_start,
                                result_pool, scratch_pool));

          SVN_ERR(grab_filename(&patch->new_filename, new_path_start,
                                result_pool, scratch_pool));
          break;
        }
    }

  /* We assume that the path is only modified until we've found a 'tree'
   * header */
  patch->operation = svn_diff_op_modified;

  *new_state = state_git_diff_seen;
  return SVN_NO_ERROR;
}