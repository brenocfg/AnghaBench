#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_4__ {int /*<<< orphan*/ * markers; int /*<<< orphan*/  output_stream; } ;
typedef  TYPE_1__ merge_output_baton_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * output_marker_eol (TYPE_1__*) ; 
 int /*<<< orphan*/  svn_stream_puts (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
output_merge_marker(merge_output_baton_t *btn, int idx)
{
  SVN_ERR(svn_stream_puts(btn->output_stream, btn->markers[idx]));
  return output_marker_eol(btn);
}