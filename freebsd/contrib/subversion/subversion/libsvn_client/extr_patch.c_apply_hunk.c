#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int current_line; scalar_t__ eol_style; char* eol_str; int /*<<< orphan*/  write_baton; int /*<<< orphan*/  (* write ) (int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ *) ;int /*<<< orphan*/  eof; } ;
typedef  TYPE_1__ target_content_t ;
struct TYPE_14__ {int len; char const* data; } ;
typedef  TYPE_2__ svn_stringbuf_t ;
typedef  int svn_linenum_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct TYPE_15__ {scalar_t__ kind_on_disk; void* has_text_changes; void* has_prop_changes; } ;
typedef  TYPE_3__ patch_target_t ;
struct TYPE_16__ {int match_fuzz; int /*<<< orphan*/  hunk; void* rejected; scalar_t__ matched_line; } ;
typedef  TYPE_4__ hunk_info_t ;
typedef  int apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 void* TRUE ; 
 int /*<<< orphan*/  copy_lines_to_target (TYPE_1__*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reject_hunk (TYPE_3__*,TYPE_1__*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  seek_to_line (TYPE_1__*,int,int /*<<< orphan*/ *) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ *) ; 
 int svn_diff_hunk_get_modified_length (int /*<<< orphan*/ ) ; 
 int svn_diff_hunk_get_original_length (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_diff_hunk_readline_modified_text (int /*<<< orphan*/ ,TYPE_2__**,char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_diff_hunk_reset_modified_text (int /*<<< orphan*/ ) ; 
 scalar_t__ svn_node_file ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ svn_subst_eol_style_none ; 

__attribute__((used)) static svn_error_t *
apply_hunk(patch_target_t *target, target_content_t *content,
           hunk_info_t *hi, const char *prop_name, apr_pool_t *pool)
{
  svn_linenum_t lines_read;
  svn_boolean_t eof;
  apr_pool_t *iterpool;
  svn_linenum_t fuzz = hi->match_fuzz;

  /* ### Is there a cleaner way to describe if we have an existing target?
   */
  if (target->kind_on_disk == svn_node_file || prop_name)
    {
      svn_linenum_t line;

      /* Move forward to the hunk's line, copying data as we go.
       * Also copy leading lines of context which matched with fuzz.
       * The target has changed on the fuzzy-matched lines,
       * so we should retain the target's version of those lines. */
      SVN_ERR(copy_lines_to_target(content, hi->matched_line + fuzz,
                                   pool));

      /* Skip the target's version of the hunk.
       * Don't skip trailing lines which matched with fuzz. */
      line = content->current_line +
             svn_diff_hunk_get_original_length(hi->hunk) - (2 * fuzz);
      SVN_ERR(seek_to_line(content, line, pool));
      if (content->current_line != line && ! content->eof)
        {
          /* Seek failed, reject this hunk. */
          hi->rejected = TRUE;
          SVN_ERR(reject_hunk(target, content, hi->hunk, prop_name, pool));
          return SVN_NO_ERROR;
        }
    }

  /* Write the hunk's version to the patched result.
   * Don't write the lines which matched with fuzz. */
  lines_read = 0;
  svn_diff_hunk_reset_modified_text(hi->hunk);
  iterpool = svn_pool_create(pool);
  do
    {
      svn_stringbuf_t *hunk_line;
      const char *eol_str;

      svn_pool_clear(iterpool);

      SVN_ERR(svn_diff_hunk_readline_modified_text(hi->hunk, &hunk_line,
                                                   &eol_str, &eof,
                                                   iterpool, iterpool));
      lines_read++;
      if (lines_read > fuzz &&
          lines_read <= svn_diff_hunk_get_modified_length(hi->hunk) - fuzz)
        {
          apr_size_t len;

          if (hunk_line->len >= 1)
            {
              len = hunk_line->len;
              SVN_ERR(content->write(content->write_baton,
                                     hunk_line->data, len, iterpool));
            }

          if (eol_str)
            {
              /* Use the EOL as it was read from the patch file,
               * unless the target's EOL style is set by svn:eol-style */
              if (content->eol_style != svn_subst_eol_style_none)
                eol_str = content->eol_str;

              len = strlen(eol_str);
              SVN_ERR(content->write(content->write_baton,
                                     eol_str, len, iterpool));
            }
        }
    }
  while (! eof);
  svn_pool_destroy(iterpool);

  if (prop_name)
    target->has_prop_changes = TRUE;
  else
    target->has_text_changes = TRUE;

  return SVN_NO_ERROR;
}