#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ sb_len; scalar_t__ save_len; TYPE_2__* buf; scalar_t__ save_pos; int /*<<< orphan*/  sb_ptr; int /*<<< orphan*/ * save_ptr; } ;
typedef  TYPE_1__ svn_spillbuf_reader_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_5__ {int /*<<< orphan*/  blocksize; int /*<<< orphan*/  pool; } ;

/* Variables and functions */
 int /*<<< orphan*/ * apr_palloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_spillbuf__write (TYPE_2__*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_spillbuf__reader_write(svn_spillbuf_reader_t *reader,
                           const char *data,
                           apr_size_t len,
                           apr_pool_t *scratch_pool)
{
  /* If we have a buffer of content from the spillbuf, then we need to
     move that content to a safe place.  */
  if (reader->sb_len > 0)
    {
      if (reader->save_ptr == NULL)
        reader->save_ptr = apr_palloc(reader->buf->pool,
                                      reader->buf->blocksize);

      memcpy(reader->save_ptr, reader->sb_ptr, reader->sb_len);
      reader->save_len = reader->sb_len;
      reader->save_pos = 0;

      /* No more content in the spillbuf-borrowed buffer.  */
      reader->sb_len = 0;
    }

  return svn_error_trace(svn_spillbuf__write(reader->buf, data, len,
                                             scratch_pool));
}