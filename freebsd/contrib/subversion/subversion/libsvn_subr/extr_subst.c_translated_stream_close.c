#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  svn_error_t ;
struct translated_stream_baton {int /*<<< orphan*/  iterpool; int /*<<< orphan*/  stream; int /*<<< orphan*/  out_baton; scalar_t__ written; } ;

/* Variables and functions */
 int /*<<< orphan*/ * svn_error_compose_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_stream_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * translate_chunk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
translated_stream_close(void *baton)
{
  struct translated_stream_baton *b = baton;
  svn_error_t *err = NULL;

  if (b->written)
    err = translate_chunk(b->stream, b->out_baton, NULL, 0, b->iterpool);

  err = svn_error_compose_create(err, svn_stream_close(b->stream));

  svn_pool_destroy(b->iterpool);

  return svn_error_trace(err);
}