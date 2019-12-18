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
struct TYPE_3__ {char* data; scalar_t__ len; } ;
typedef  TYPE_1__ svn_stringbuf_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
struct base85_baton_t {scalar_t__ buf_size; scalar_t__ buf_pos; scalar_t__ next_pos; scalar_t__ end_pos; scalar_t__ buffer; scalar_t__ done; int /*<<< orphan*/  file; int /*<<< orphan*/ * iterpool; } ;
typedef  scalar_t__ apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_SET ; 
 int /*<<< orphan*/  APR_SIZE_MAX ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_DIFF_UNEXPECTED_DATA ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  memcpy (char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  svn_diff__base85_decode_line (scalar_t__,int,char*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_io_file_get_offset (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_file_readline (int /*<<< orphan*/ ,TYPE_1__**,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_file_seek (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
read_handler_base85(void *baton, char *buffer, apr_size_t *len)
{
  struct base85_baton_t *b85b = baton;
  apr_pool_t *iterpool = b85b->iterpool;
  apr_size_t remaining = *len;
  char *dest = buffer;

  svn_pool_clear(iterpool);

  if (b85b->done)
    {
      *len = 0;
      return SVN_NO_ERROR;
    }

  while (remaining && (b85b->buf_size > b85b->buf_pos
                       || b85b->next_pos < b85b->end_pos))
    {
      svn_stringbuf_t *line;
      svn_boolean_t at_eof;

      apr_size_t available = b85b->buf_size - b85b->buf_pos;
      if (available)
        {
          apr_size_t n = (remaining < available) ? remaining : available;

          memcpy(dest, b85b->buffer + b85b->buf_pos, n);
          dest += n;
          remaining -= n;
          b85b->buf_pos += n;

          if (!remaining)
            return SVN_NO_ERROR; /* *len = OK */
        }

      if (b85b->next_pos >= b85b->end_pos)
        break; /* At EOF */
      SVN_ERR(svn_io_file_seek(b85b->file, APR_SET, &b85b->next_pos,
                               iterpool));
      SVN_ERR(svn_io_file_readline(b85b->file, &line, NULL, &at_eof,
                                   APR_SIZE_MAX, iterpool, iterpool));
      if (at_eof)
        b85b->next_pos = b85b->end_pos;
      else
        {
          SVN_ERR(svn_io_file_get_offset(&b85b->next_pos, b85b->file,
                                         iterpool));
        }

      if (line->len && line->data[0] >= 'A' && line->data[0] <= 'Z')
        b85b->buf_size = line->data[0] - 'A' + 1;
      else if (line->len && line->data[0] >= 'a' && line->data[0] <= 'z')
        b85b->buf_size = line->data[0] - 'a' + 26 + 1;
      else
        return svn_error_create(SVN_ERR_DIFF_UNEXPECTED_DATA, NULL,
                                _("Unexpected data in base85 section"));

      if (b85b->buf_size < 52)
        b85b->next_pos = b85b->end_pos; /* Handle as EOF */

      SVN_ERR(svn_diff__base85_decode_line(b85b->buffer, b85b->buf_size,
                                           line->data + 1, line->len - 1,
                                           iterpool));
      b85b->buf_pos = 0;
    }

  *len -= remaining;
  b85b->done = TRUE;

  return SVN_NO_ERROR;
}