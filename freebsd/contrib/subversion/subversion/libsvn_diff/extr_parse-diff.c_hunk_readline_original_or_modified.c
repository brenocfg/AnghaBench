#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {char* data; } ;
typedef  TYPE_1__ svn_stringbuf_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int svn_boolean_t ;
struct svn_diff__hunk_range {scalar_t__ current; scalar_t__ end; } ;
typedef  scalar_t__ apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  scalar_t__ apr_off_t ;
typedef  int /*<<< orphan*/  apr_file_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_SET ; 
 scalar_t__ APR_SIZE_MAX ; 
 int FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int TRUE ; 
 int /*<<< orphan*/  svn_io_file_get_offset (scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_file_readline (int /*<<< orphan*/ *,TYPE_1__**,char const**,int*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_file_seek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_stringbuf_create (char*,int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_stringbuf_create_empty (int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_stringbuf_create_ensure (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_stringbuf_dup (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
hunk_readline_original_or_modified(apr_file_t *file,
                                   struct svn_diff__hunk_range *range,
                                   svn_stringbuf_t **stringbuf,
                                   const char **eol,
                                   svn_boolean_t *eof,
                                   char verboten,
                                   svn_boolean_t no_final_eol,
                                   apr_pool_t *result_pool,
                                   apr_pool_t *scratch_pool)
{
  apr_size_t max_len;
  svn_boolean_t filtered;
  apr_off_t pos;
  svn_stringbuf_t *str;
  const char *eol_p;
  apr_pool_t *last_pool;

  if (!eol)
    eol = &eol_p;

  if (range->current >= range->end)
    {
      /* We're past the range. Indicate that no bytes can be read. */
      *eof = TRUE;
      *eol = NULL;
      *stringbuf = svn_stringbuf_create_empty(result_pool);
      return SVN_NO_ERROR;
    }

  SVN_ERR(svn_io_file_get_offset(&pos, file, scratch_pool));
  SVN_ERR(svn_io_file_seek(file, APR_SET, &range->current, scratch_pool));

  /* It's not ITERPOOL because we use data allocated in LAST_POOL out
     of the loop. */
  last_pool = svn_pool_create(scratch_pool);
  do
    {
      svn_pool_clear(last_pool);

      max_len = range->end - range->current;
      SVN_ERR(svn_io_file_readline(file, &str, eol, eof, max_len,
                                   last_pool, last_pool));
      SVN_ERR(svn_io_file_get_offset(&range->current, file, last_pool));
      filtered = (str->data[0] == verboten || str->data[0] == '\\');
    }
  while (filtered && ! *eof);

  if (filtered)
    {
      /* EOF, return an empty string. */
      *stringbuf = svn_stringbuf_create_ensure(0, result_pool);
      *eol = NULL;
    }
  else if (str->data[0] == '+' || str->data[0] == '-' || str->data[0] == ' ')
    {
      /* Shave off leading unidiff symbols. */
      *stringbuf = svn_stringbuf_create(str->data + 1, result_pool);
    }
  else
    {
      /* Return the line as-is. Handle as a chopped leading spaces */
      *stringbuf = svn_stringbuf_dup(str, result_pool);
    }

  if (!filtered && *eof && !*eol && *str->data)
    {
      /* Ok, we miss a final EOL in the patch file, but didn't see a
         no eol marker line.

         We should report that we had an EOL or the patch code will
         misbehave (and it knows nothing about no eol markers) */

      if (!no_final_eol && eol != &eol_p)
        {
          apr_off_t start = 0;

          SVN_ERR(svn_io_file_seek(file, APR_SET, &start, scratch_pool));

          SVN_ERR(svn_io_file_readline(file, &str, eol, NULL, APR_SIZE_MAX,
                                       scratch_pool, scratch_pool));

          /* Every patch file that has hunks has at least one EOL*/
          SVN_ERR_ASSERT(*eol != NULL);
        }

      *eof = FALSE;
      /* Fall through to seek back to the right location */
    }
  SVN_ERR(svn_io_file_seek(file, APR_SET, &pos, scratch_pool));

  svn_pool_destroy(last_pool);
  return SVN_NO_ERROR;
}