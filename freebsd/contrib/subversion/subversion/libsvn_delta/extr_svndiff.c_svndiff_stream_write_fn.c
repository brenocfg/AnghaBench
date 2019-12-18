#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  window_buffer; } ;
typedef  TYPE_1__ svndiff_stream_baton_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_size_t ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  svn_stringbuf_appendbytes (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
svndiff_stream_write_fn(void *baton, const char *data, apr_size_t *len)
{
  svndiff_stream_baton_t *b = baton;

  /* The memory usage here is limited, as this buffer doesn't grow
     beyond the (header size + max window size in svndiff format).
     See the comment in svn_txdelta_to_svndiff_stream().  */
  svn_stringbuf_appendbytes(b->window_buffer, data, *len);

  return SVN_NO_ERROR;
}