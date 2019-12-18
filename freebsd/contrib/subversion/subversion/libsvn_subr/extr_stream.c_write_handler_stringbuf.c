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
struct stringbuf_stream_baton {int /*<<< orphan*/  str; } ;
typedef  int /*<<< orphan*/  apr_size_t ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  svn_stringbuf_appendbytes (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
write_handler_stringbuf(void *baton, const char *data, apr_size_t *len)
{
  struct stringbuf_stream_baton *btn = baton;

  svn_stringbuf_appendbytes(btn->str, data, *len);
  return SVN_NO_ERROR;
}