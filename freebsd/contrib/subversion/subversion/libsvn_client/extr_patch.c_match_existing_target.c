#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ eof; int /*<<< orphan*/  keywords; int /*<<< orphan*/  current_line; } ;
typedef  TYPE_1__ target_content_t ;
struct TYPE_8__ {char const* data; } ;
typedef  TYPE_2__ svn_stringbuf_t ;
typedef  int /*<<< orphan*/  svn_linenum_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_diff_hunk_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  readline (TYPE_1__*,char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  seek_to_line (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcmp (char const*,char const*) ; 
 int /*<<< orphan*/  svn_diff_hunk_readline_modified_text (int /*<<< orphan*/ *,TYPE_2__**,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_diff_hunk_reset_modified_text (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_subst_translate_cstring2 (char const*,char const**,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
match_existing_target(svn_boolean_t *match,
                      target_content_t *content,
                      svn_diff_hunk_t *hunk,
                      apr_pool_t *scratch_pool)
{
  svn_boolean_t lines_matched;
  apr_pool_t *iterpool;
  svn_boolean_t hunk_eof;
  svn_linenum_t saved_line;

  svn_diff_hunk_reset_modified_text(hunk);

  saved_line = content->current_line;

  iterpool = svn_pool_create(scratch_pool);
  do
    {
      const char *line;
      svn_stringbuf_t *hunk_line;
      const char *line_translated;
      const char *hunk_line_translated;

      svn_pool_clear(iterpool);

      SVN_ERR(readline(content, &line, iterpool, iterpool));
      SVN_ERR(svn_diff_hunk_readline_modified_text(hunk, &hunk_line,
                                                   NULL, &hunk_eof,
                                                   iterpool, iterpool));
      /* Contract keywords. */
      SVN_ERR(svn_subst_translate_cstring2(line, &line_translated,
                                           NULL, FALSE,
                                           content->keywords,
                                           FALSE, iterpool));
      SVN_ERR(svn_subst_translate_cstring2(hunk_line->data,
                                           &hunk_line_translated,
                                           NULL, FALSE,
                                           content->keywords,
                                           FALSE, iterpool));
      lines_matched = ! strcmp(line_translated, hunk_line_translated);
      if (content->eof != hunk_eof)
        {
          svn_pool_destroy(iterpool);
          *match = FALSE;
          return SVN_NO_ERROR;
        }
    }
  while (lines_matched && ! content->eof && ! hunk_eof);
  svn_pool_destroy(iterpool);

  *match = (lines_matched && content->eof == hunk_eof);
  SVN_ERR(seek_to_line(content, saved_line, scratch_pool));

  return SVN_NO_ERROR;
}