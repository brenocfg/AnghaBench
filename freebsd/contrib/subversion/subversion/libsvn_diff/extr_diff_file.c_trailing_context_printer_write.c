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
typedef  int /*<<< orphan*/  svn_error_t ;
struct trailing_context_printer {scalar_t__ lines_to_print; TYPE_1__* fob; } ;
typedef  int /*<<< orphan*/  apr_size_t ;
struct TYPE_2__ {int /*<<< orphan*/  real_output_stream; } ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  make_context_saver (TYPE_1__*) ; 
 int /*<<< orphan*/  svn_stream_write (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
trailing_context_printer_write(void *baton,
                               const char *data,
                               apr_size_t *len)
{
  struct trailing_context_printer *tcp = baton;
  SVN_ERR_ASSERT(tcp->lines_to_print > 0);
  SVN_ERR(svn_stream_write(tcp->fob->real_output_stream, data, len));
  tcp->lines_to_print--;
  if (tcp->lines_to_print == 0)
    make_context_saver(tcp->fob);
  return SVN_NO_ERROR;
}