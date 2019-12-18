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
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_3__ {scalar_t__* current_line; } ;
typedef  TYPE_1__ svn_diff3__file_output_baton_t ;
typedef  scalar_t__ apr_off_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  output_line (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  svn_diff3__file_output_normal ; 
 int /*<<< orphan*/  svn_diff3__file_output_skip ; 

__attribute__((used)) static svn_error_t *
output_hunk(void *baton, int idx, apr_off_t target_line,
            apr_off_t target_length)
{
  svn_diff3__file_output_baton_t *output_baton = baton;

  /* Skip lines until we are at the start of the changed range */
  while (output_baton->current_line[idx] < target_line)
    {
      SVN_ERR(output_line(output_baton, svn_diff3__file_output_skip, idx));
    }

  target_line += target_length;

  while (output_baton->current_line[idx] < target_line)
    {
      SVN_ERR(output_line(output_baton, svn_diff3__file_output_normal, idx));
    }

  return SVN_NO_ERROR;
}