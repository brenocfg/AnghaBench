#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_stream_mark_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct translated_stream_baton {scalar_t__ readbuf_off; int /*<<< orphan*/  readbuf; scalar_t__ written; TYPE_5__* out_baton; TYPE_3__* in_baton; int /*<<< orphan*/  stream; int /*<<< orphan*/  buf; int /*<<< orphan*/  iterpool; } ;
struct TYPE_7__ {int /*<<< orphan*/  buf; scalar_t__ readbuf_off; TYPE_1__* readbuf; scalar_t__ written; TYPE_5__* out_baton; TYPE_3__* in_baton; } ;
struct TYPE_9__ {TYPE_2__ saved_baton; int /*<<< orphan*/  mark; } ;
typedef  TYPE_4__ mark_translated_t ;
struct TYPE_10__ {scalar_t__ src_format_len; scalar_t__ keyword_off; scalar_t__ newline_off; } ;
struct TYPE_8__ {scalar_t__ src_format_len; scalar_t__ keyword_off; scalar_t__ newline_off; } ;
struct TYPE_6__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN__TRANSLATION_BUF_SIZE ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_stream_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_stream_seek (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_stringbuf_appendbytes (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_stringbuf_setempty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  translate_chunk (int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
translated_stream_seek(void *baton, const svn_stream_mark_t *mark)
{
  struct translated_stream_baton *b = baton;

  if (mark != NULL)
    {
      const mark_translated_t *mt = (const mark_translated_t *)mark;

      /* Flush output buffer if necessary. */
      if (b->written)
        SVN_ERR(translate_chunk(b->stream, b->out_baton, NULL, 0,
                                b->iterpool));

      SVN_ERR(svn_stream_seek(b->stream, mt->mark));

      /* Restore translation state, avoiding new allocations. */
      *b->in_baton = *mt->saved_baton.in_baton;
      *b->out_baton = *mt->saved_baton.out_baton;
      b->written = mt->saved_baton.written;
      svn_stringbuf_setempty(b->readbuf);
      svn_stringbuf_appendbytes(b->readbuf, mt->saved_baton.readbuf->data,
                                mt->saved_baton.readbuf->len);
      b->readbuf_off = mt->saved_baton.readbuf_off;
      memcpy(b->buf, mt->saved_baton.buf, SVN__TRANSLATION_BUF_SIZE);
    }
  else
    {
      SVN_ERR(svn_stream_reset(b->stream));

      b->in_baton->newline_off = 0;
      b->in_baton->keyword_off = 0;
      b->in_baton->src_format_len = 0;
      b->out_baton->newline_off = 0;
      b->out_baton->keyword_off = 0;
      b->out_baton->src_format_len = 0;

      b->written = FALSE;
      svn_stringbuf_setempty(b->readbuf);
      b->readbuf_off = 0;
    }

  return SVN_NO_ERROR;
}