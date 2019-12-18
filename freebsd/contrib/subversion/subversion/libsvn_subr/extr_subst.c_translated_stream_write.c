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
struct translated_stream_baton {int /*<<< orphan*/  iterpool; int /*<<< orphan*/  out_baton; int /*<<< orphan*/  stream; int /*<<< orphan*/  written; } ;
typedef  int /*<<< orphan*/  apr_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * translate_chunk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
translated_stream_write(void *baton,
                        const char *buffer,
                        apr_size_t *len)
{
  struct translated_stream_baton *b = baton;
  svn_pool_clear(b->iterpool);

  b->written = TRUE;
  return translate_chunk(b->stream, b->out_baton, buffer, *len, b->iterpool);
}