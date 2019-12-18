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
typedef  scalar_t__ svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int COLS ; 
 int ROWS ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 char* apr_psprintf (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 int /*<<< orphan*/  stdout ; 
 scalar_t__ strcmp (char const*,char const*) ; 
 scalar_t__ strlen (char const*) ; 
 int /*<<< orphan*/  svn_cmdline_fputs (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_cmdline_printf (int /*<<< orphan*/ *,char*,int,...) ; 
 int /*<<< orphan*/  svn_uri_skip_ancestor (char const*,char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
mergeinfo_diagram(const char *yca_url,
                  const char *base_url,
                  const char *right_url,
                  const char *target_url,
                  svn_revnum_t yca_rev,
                  svn_revnum_t base_rev,
                  svn_revnum_t right_rev,
                  svn_revnum_t target_rev,
                  const char *repos_root_url,
                  svn_boolean_t target_is_wc,
                  svn_boolean_t reintegrate_like,
                  apr_pool_t *pool)
{
  /* The graph occupies 4 rows of text, and the annotations occupy
   * another 2 rows above and 2 rows below.  The graph is constructed
   * from left to right in discrete sections ("columns"), each of which
   * can have a different width (measured in characters).  Each element in
   * the array is either a text string of the appropriate width, or can
   * be NULL to draw a blank cell. */
#define ROWS 8
#define COLS 4
  const char *g[ROWS][COLS] = {{0}};
  int col_width[COLS];
  int row, col;

  /* The YCA (that is, the branching point).  And an ellipsis, because we
   * don't show information about earlier merges */
  g[0][0] = apr_psprintf(pool, "  %-8ld  ", yca_rev);
  g[1][0] =     "  |         ";
  if (strcmp(yca_url, right_url) == 0)
    {
      g[2][0] = "-------| |--";
      g[3][0] = "   \\        ";
      g[4][0] = "    \\       ";
      g[5][0] = "     --| |--";
    }
  else if (strcmp(yca_url, target_url) == 0)
    {
      g[2][0] = "     --| |--";
      g[3][0] = "    /       ";
      g[4][0] = "   /        ";
      g[5][0] = "-------| |--";
    }
  else
    {
      g[2][0] = "     --| |--";
      g[3][0] = "... /       ";
      g[4][0] = "    \\       ";
      g[5][0] = "     --| |--";
    }

  /* The last full merge */
  if ((base_rev > yca_rev) && reintegrate_like)
    {
      g[2][2] = "---------";
      g[3][2] = "  /      ";
      g[4][2] = " /       ";
      g[5][2] = "---------";
      g[6][2] = "|        ";
      g[7][2] = apr_psprintf(pool, "%-8ld ", base_rev);
    }
  else if (base_rev > yca_rev)
    {
      g[0][2] = apr_psprintf(pool, "%-8ld ", base_rev);
      g[1][2] = "|        ";
      g[2][2] = "---------";
      g[3][2] = " \\       ";
      g[4][2] = "  \\      ";
      g[5][2] = "---------";
    }
  else
    {
      g[2][2] = "---------";
      g[3][2] = "         ";
      g[4][2] = "         ";
      g[5][2] = "---------";
    }

  /* The tips of the branches */
    {
      g[0][3] = apr_psprintf(pool, "%-8ld", right_rev);
      g[1][3] = "|       ";
      g[2][3] = "-       ";
      g[3][3] = "        ";
      g[4][3] = "        ";
      g[5][3] = "-       ";
      g[6][3] = "|       ";
      g[7][3] = target_is_wc ? "WC      "
                             : apr_psprintf(pool, "%-8ld", target_rev);
    }

  /* Find the width of each column, so we know how to print blank cells */
  for (col = 0; col < COLS; col++)
    {
      col_width[col] = 0;
      for (row = 0; row < ROWS; row++)
        {
          if (g[row][col] && ((int)strlen(g[row][col]) > col_width[col]))
            col_width[col] = (int)strlen(g[row][col]);
        }
    }

  /* Column headings */
  SVN_ERR(svn_cmdline_printf(pool,
            "    %s\n"
            "    |         %s\n"
            "    |         |        %s\n"
            "    |         |        |         %s\n"
            "\n",
            _("youngest common ancestor"), _("last full merge"),
            _("tip of branch"), _("repository path")));

  /* Print the diagram, row by row */
  for (row = 0; row < ROWS; row++)
    {
      SVN_ERR(svn_cmdline_fputs("  ", stdout, pool));
      for (col = 0; col < COLS; col++)
        {
          if (g[row][col])
            {
              SVN_ERR(svn_cmdline_fputs(g[row][col], stdout, pool));
            }
          else
            {
              /* Print <column-width> spaces */
              SVN_ERR(svn_cmdline_printf(pool, "%*s", col_width[col], ""));
            }
        }
      if (row == 2)
        SVN_ERR(svn_cmdline_printf(pool, "  %s",
                svn_uri_skip_ancestor(repos_root_url, right_url, pool)));
      if (row == 5)
        SVN_ERR(svn_cmdline_printf(pool, "  %s",
                svn_uri_skip_ancestor(repos_root_url, target_url, pool)));
      SVN_ERR(svn_cmdline_fputs("\n", stdout, pool));
    }

  return SVN_NO_ERROR;
}