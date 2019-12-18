#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {char* data; } ;
typedef  TYPE_3__ svn_stringbuf_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_9__ {scalar_t__ current; scalar_t__ end; } ;
struct TYPE_12__ {TYPE_2__* patch; int /*<<< orphan*/  apr_file; TYPE_1__ diff_text_range; } ;
typedef  TYPE_4__ svn_diff_hunk_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  scalar_t__ apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  scalar_t__ apr_off_t ;
struct TYPE_10__ {scalar_t__ reverse; } ;

/* Variables and functions */
 int /*<<< orphan*/  APR_SET ; 
 scalar_t__ APR_SIZE_MAX ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  svn_io_file_get_offset (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_file_readline (int /*<<< orphan*/ ,TYPE_3__**,char const**,scalar_t__*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_file_seek (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ *) ; 
 TYPE_3__* svn_stringbuf_create_empty (int /*<<< orphan*/ *) ; 

svn_error_t *
svn_diff_hunk_readline_diff_text(svn_diff_hunk_t *hunk,
                                 svn_stringbuf_t **stringbuf,
                                 const char **eol,
                                 svn_boolean_t *eof,
                                 apr_pool_t *result_pool,
                                 apr_pool_t *scratch_pool)
{
  svn_stringbuf_t *line;
  apr_size_t max_len;
  apr_off_t pos;
  const char *eol_p;

  if (!eol)
    eol = &eol_p;

  if (hunk->diff_text_range.current >= hunk->diff_text_range.end)
    {
      /* We're past the range. Indicate that no bytes can be read. */
      *eof = TRUE;
      *eol = NULL;
      *stringbuf = svn_stringbuf_create_empty(result_pool);
      return SVN_NO_ERROR;
    }

  SVN_ERR(svn_io_file_get_offset(&pos, hunk->apr_file, scratch_pool));
  SVN_ERR(svn_io_file_seek(hunk->apr_file, APR_SET,
                           &hunk->diff_text_range.current, scratch_pool));
  max_len = hunk->diff_text_range.end - hunk->diff_text_range.current;
  SVN_ERR(svn_io_file_readline(hunk->apr_file, &line, eol, eof, max_len,
                               result_pool,
                   scratch_pool));
  SVN_ERR(svn_io_file_get_offset(&hunk->diff_text_range.current,
                                 hunk->apr_file, scratch_pool));

  if (*eof && !*eol && *line->data)
    {
      /* Ok, we miss a final EOL in the patch file, but didn't see a
          no eol marker line.

          We should report that we had an EOL or the patch code will
          misbehave (and it knows nothing about no eol markers) */

      if (eol != &eol_p)
        {
          /* Lets pick the first eol we find in our patch file */
          apr_off_t start = 0;
          svn_stringbuf_t *str;

          SVN_ERR(svn_io_file_seek(hunk->apr_file, APR_SET, &start,
                                   scratch_pool));

          SVN_ERR(svn_io_file_readline(hunk->apr_file, &str, eol, NULL,
                                       APR_SIZE_MAX,
                                       scratch_pool, scratch_pool));

          /* Every patch file that has hunks has at least one EOL*/
          SVN_ERR_ASSERT(*eol != NULL);
        }

      *eof = FALSE;

      /* Fall through to seek back to the right location */
    }

  SVN_ERR(svn_io_file_seek(hunk->apr_file, APR_SET, &pos, scratch_pool));

  if (hunk->patch->reverse)
    {
      if (line->data[0] == '+')
        line->data[0] = '-';
      else if (line->data[0] == '-')
        line->data[0] = '+';
    }

  *stringbuf = line;

  return SVN_NO_ERROR;
}