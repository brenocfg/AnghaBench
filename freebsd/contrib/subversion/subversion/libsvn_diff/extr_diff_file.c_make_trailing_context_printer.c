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
struct TYPE_3__ {int /*<<< orphan*/ * output_stream; int /*<<< orphan*/  pool; int /*<<< orphan*/  context_size; } ;
typedef  TYPE_1__ svn_diff3__file_output_baton_t ;
struct trailing_context_printer {TYPE_1__* fob; int /*<<< orphan*/  lines_to_print; } ;

/* Variables and functions */
 struct trailing_context_printer* apr_pcalloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_stream_empty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_stream_set_baton (int /*<<< orphan*/ *,struct trailing_context_printer*) ; 
 int /*<<< orphan*/  svn_stream_set_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trailing_context_printer_write ; 

__attribute__((used)) static void
make_trailing_context_printer(svn_diff3__file_output_baton_t *btn)
{
  struct trailing_context_printer *tcp;
  svn_stream_t *s;

  svn_pool_clear(btn->pool);

  tcp = apr_pcalloc(btn->pool, sizeof(*tcp));
  tcp->lines_to_print = btn->context_size;
  tcp->fob = btn;
  s = svn_stream_empty(btn->pool);
  svn_stream_set_baton(s, tcp);
  svn_stream_set_write(s, trailing_context_printer_write);
  btn->output_stream = s;
}