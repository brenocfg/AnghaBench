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
typedef  int /*<<< orphan*/  svn_stream_mark_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct translated_stream_baton {int /*<<< orphan*/  buf; int /*<<< orphan*/  readbuf_off; int /*<<< orphan*/  readbuf; int /*<<< orphan*/  written; int /*<<< orphan*/  out_baton; int /*<<< orphan*/  in_baton; int /*<<< orphan*/  stream; } ;
struct TYPE_4__ {void* buf; int /*<<< orphan*/  readbuf_off; int /*<<< orphan*/  readbuf; int /*<<< orphan*/  written; void* out_baton; void* in_baton; } ;
struct TYPE_5__ {TYPE_1__ saved_baton; int /*<<< orphan*/  mark; } ;
typedef  TYPE_2__ mark_translated_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int SVN__TRANSLATION_BUF_SIZE ; 
 TYPE_2__* apr_palloc (int /*<<< orphan*/ *,int) ; 
 void* apr_pmemdup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  svn_stream_mark (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stringbuf_dup (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
translated_stream_mark(void *baton, svn_stream_mark_t **mark, apr_pool_t *pool)
{
  mark_translated_t *mt;
  struct translated_stream_baton *b = baton;

  mt = apr_palloc(pool, sizeof(*mt));
  SVN_ERR(svn_stream_mark(b->stream, &mt->mark, pool));

  /* Save translation state. */
  mt->saved_baton.in_baton = apr_pmemdup(pool, b->in_baton,
                                         sizeof(*mt->saved_baton.in_baton));
  mt->saved_baton.out_baton = apr_pmemdup(pool, b->out_baton,
                                          sizeof(*mt->saved_baton.out_baton));
  mt->saved_baton.written = b->written;
  mt->saved_baton.readbuf = svn_stringbuf_dup(b->readbuf, pool);
  mt->saved_baton.readbuf_off = b->readbuf_off;
  mt->saved_baton.buf = apr_pmemdup(pool, b->buf, SVN__TRANSLATION_BUF_SIZE);

  *mark = (svn_stream_mark_t *)mt;

  return SVN_NO_ERROR;
}