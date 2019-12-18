#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ context_size; int /*<<< orphan*/  pool; int /*<<< orphan*/  output_stream; TYPE_2__* context_saver; } ;
typedef  TYPE_1__ svn_diff3__file_output_baton_t ;
struct TYPE_6__ {scalar_t__ context_size; void* len; void* data; int /*<<< orphan*/  stream; } ;
typedef  TYPE_2__ context_saver_t ;

/* Variables and functions */
 void* apr_pcalloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  context_saver_stream_write ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_stream_empty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_stream_set_baton (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  svn_stream_set_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
make_context_saver(svn_diff3__file_output_baton_t *fob)
{
  context_saver_t *cs;

  assert(fob->context_size > 0); /* Or nothing to save */

  svn_pool_clear(fob->pool);
  cs = apr_pcalloc(fob->pool, sizeof(*cs));
  cs->stream = svn_stream_empty(fob->pool);
  svn_stream_set_baton(cs->stream, cs);
  svn_stream_set_write(cs->stream, context_saver_stream_write);
  fob->context_saver = cs;
  fob->output_stream = cs->stream;
  cs->context_size = fob->context_size;
  cs->data = apr_pcalloc(fob->pool, sizeof(*cs->data) * cs->context_size);
  cs->len = apr_pcalloc(fob->pool, sizeof(*cs->len) * cs->context_size);
}