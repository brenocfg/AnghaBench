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
typedef  int /*<<< orphan*/  svn_diff_datasource_e ;
typedef  int /*<<< orphan*/  apr_size_t ;
typedef  scalar_t__ apr_off_t ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 

__attribute__((used)) static svn_error_t *
datasources_open(void *baton,
                 apr_off_t *prefix_lines,
                 apr_off_t *suffix_lines,
                 const svn_diff_datasource_e *datasources,
                 apr_size_t datasources_len)
{
  /* Do nothing: everything is already there and initialized to 0 */
  *prefix_lines = 0;
  *suffix_lines = 0;
  return SVN_NO_ERROR;
}