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
typedef  int /*<<< orphan*/  svn_patch_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  enum parse_state { ____Placeholder_parse_state } parse_state ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int state_binary_patch_found ; 

__attribute__((used)) static svn_error_t *
binary_patch_start(enum parse_state *new_state, char *line, svn_patch_t *patch,
             apr_pool_t *result_pool, apr_pool_t *scratch_pool)
{
  *new_state = state_binary_patch_found;
  return SVN_NO_ERROR;
}