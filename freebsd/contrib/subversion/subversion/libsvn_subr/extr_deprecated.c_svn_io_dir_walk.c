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
typedef  int /*<<< orphan*/  svn_io_walk_func_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct walk_func_filter_baton_t {void* walk_baton; int /*<<< orphan*/  walk_func; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_int32_t ;

/* Variables and functions */
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_io_dir_walk2 (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct walk_func_filter_baton_t*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  walk_func_filter_func ; 

svn_error_t *
svn_io_dir_walk(const char *dirname,
                apr_int32_t wanted,
                svn_io_walk_func_t walk_func,
                void *walk_baton,
                apr_pool_t *pool)
{
  struct walk_func_filter_baton_t baton;
  baton.walk_func = walk_func;
  baton.walk_baton = walk_baton;
  return svn_error_trace(svn_io_dir_walk2(dirname, wanted,
                                          walk_func_filter_func,
                                          &baton, pool));
}