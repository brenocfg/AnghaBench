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
struct TYPE_3__ {scalar_t__ save_len; scalar_t__ save_ptr; scalar_t__ save_pos; scalar_t__ sb_len; scalar_t__ sb_ptr; int /*<<< orphan*/  buf; } ;
typedef  TYPE_1__ svn_spillbuf_reader_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_INCORRECT_PARAMS ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  memcpy (char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_spillbuf__read (int /*<<< orphan*/ **,scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_spillbuf__reader_read(apr_size_t *amt,
                          svn_spillbuf_reader_t *reader,
                          char *data,
                          apr_size_t len,
                          apr_pool_t *scratch_pool)
{
  if (len == 0)
    return svn_error_create(SVN_ERR_INCORRECT_PARAMS, NULL, NULL);

  *amt = 0;

  while (len > 0)
    {
      apr_size_t copy_amt;

      if (reader->save_len > 0)
        {
          /* We have some saved content, so use this first.  */

          if (len < reader->save_len)
            copy_amt = len;
          else
            copy_amt = reader->save_len;

          memcpy(data, reader->save_ptr + reader->save_pos, copy_amt);
          reader->save_pos += copy_amt;
          reader->save_len -= copy_amt;
        }
      else
        {
          /* No saved content. We should now copy from spillbuf-provided
             buffers of content.  */

          /* We may need more content from the spillbuf.  */
          if (reader->sb_len == 0)
            {
              SVN_ERR(svn_spillbuf__read(&reader->sb_ptr, &reader->sb_len,
                                         reader->buf,
                                         scratch_pool));

              /* We've run out of content, so return with whatever has
                 been copied into DATA and stored into AMT.  */
              if (reader->sb_ptr == NULL)
                {
                  /* For safety, read() may not have set SB_LEN. We use it
                     as an indicator, so it needs to be cleared.  */
                  reader->sb_len = 0;
                  return SVN_NO_ERROR;
                }
            }

          if (len < reader->sb_len)
            copy_amt = len;
          else
            copy_amt = reader->sb_len;

          memcpy(data, reader->sb_ptr, copy_amt);
          reader->sb_ptr += copy_amt;
          reader->sb_len -= copy_amt;
        }

      data += copy_amt;
      len -= copy_amt;
      (*amt) += copy_amt;
    }

  return SVN_NO_ERROR;
}