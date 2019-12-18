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
typedef  int /*<<< orphan*/  svn_stream_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct translated_stream_baton {scalar_t__ readbuf_off; TYPE_1__* readbuf; int /*<<< orphan*/  iterpool; int /*<<< orphan*/  in_baton; int /*<<< orphan*/ * buf; int /*<<< orphan*/  stream; } ;
typedef  int apr_size_t ;
struct TYPE_3__ {scalar_t__ len; char* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int SVN__STREAM_CHUNK_SIZE ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_stream_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_stream_from_stringbuf (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_stream_read_full (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  svn_stringbuf_setempty (TYPE_1__*) ; 
 int /*<<< orphan*/  translate_chunk (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
translated_stream_read(void *baton,
                       char *buffer,
                       apr_size_t *len)
{
  struct translated_stream_baton *b = baton;
  apr_size_t readlen = SVN__STREAM_CHUNK_SIZE;
  apr_size_t unsatisfied = *len;
  apr_size_t off = 0;

  /* Optimization for a frequent special case. The configuration parser (and
     a few others) reads the stream one byte at a time. All the memcpy, pool
     clearing etc. imposes a huge overhead in that case. In most cases, we
     can just take that single byte directly from the read buffer.

     Since *len > 1 requires lots of code to be run anyways, we can afford
     the extra overhead of checking for *len == 1.

     See <http://mail-archives.apache.org/mod_mbox/subversion-dev/201003.mbox/%3C4B94011E.1070207@alice-dsl.de%3E>.
  */
  if (unsatisfied == 1 && b->readbuf_off < b->readbuf->len)
    {
      /* Just take it from the read buffer */
      *buffer = b->readbuf->data[b->readbuf_off++];

      return SVN_NO_ERROR;
    }

  /* Standard code path. */
  while (readlen == SVN__STREAM_CHUNK_SIZE && unsatisfied > 0)
    {
      apr_size_t to_copy;
      apr_size_t buffer_remainder;

      svn_pool_clear(b->iterpool);
      /* fill read buffer, if necessary */
      if (! (b->readbuf_off < b->readbuf->len))
        {
          svn_stream_t *buf_stream;

          svn_stringbuf_setempty(b->readbuf);
          b->readbuf_off = 0;
          SVN_ERR(svn_stream_read_full(b->stream, b->buf, &readlen));
          buf_stream = svn_stream_from_stringbuf(b->readbuf, b->iterpool);

          SVN_ERR(translate_chunk(buf_stream, b->in_baton, b->buf,
                                  readlen, b->iterpool));

          if (readlen != SVN__STREAM_CHUNK_SIZE)
            SVN_ERR(translate_chunk(buf_stream, b->in_baton, NULL, 0,
                                    b->iterpool));

          SVN_ERR(svn_stream_close(buf_stream));
        }

      /* Satisfy from the read buffer */
      buffer_remainder = b->readbuf->len - b->readbuf_off;
      to_copy = (buffer_remainder > unsatisfied)
        ? unsatisfied : buffer_remainder;
      memcpy(buffer + off, b->readbuf->data + b->readbuf_off, to_copy);
      off += to_copy;
      b->readbuf_off += to_copy;
      unsatisfied -= to_copy;
    }

  *len -= unsatisfied;

  return SVN_NO_ERROR;
}