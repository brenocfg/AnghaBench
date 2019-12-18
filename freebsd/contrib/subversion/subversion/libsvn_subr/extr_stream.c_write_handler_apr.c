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
struct baton_apr {int /*<<< orphan*/  pool; int /*<<< orphan*/  file; } ;
typedef  int apr_size_t ;

/* Variables and functions */
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_io_file_putc (char const,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_io_file_write_full (int /*<<< orphan*/ ,char const*,int,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
write_handler_apr(void *baton, const char *data, apr_size_t *len)
{
  struct baton_apr *btn = baton;
  svn_error_t *err;

  if (*len == 1)
    {
      err = svn_io_file_putc(*data, btn->file, btn->pool);
      if (err)
        *len = 0;
    }
  else
    err = svn_io_file_write_full(btn->file, data, *len, len, btn->pool);

  return svn_error_trace(err);
}