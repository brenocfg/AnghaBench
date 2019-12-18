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
struct walk_func_filter_baton_t {int /*<<< orphan*/  walk_baton; int /*<<< orphan*/  (* walk_func ) (int /*<<< orphan*/ ,char const*,TYPE_1__ const*,int /*<<< orphan*/ *) ;} ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_4__ {scalar_t__ filetype; } ;
typedef  TYPE_1__ apr_finfo_t ;

/* Variables and functions */
 scalar_t__ APR_DIR ; 
 scalar_t__ APR_REG ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char const*,TYPE_1__ const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
walk_func_filter_func(void *baton,
                      const char *path,
                      const apr_finfo_t *finfo,
                      apr_pool_t *pool)
{
  struct walk_func_filter_baton_t *b = baton;

  if (finfo->filetype == APR_DIR || finfo->filetype == APR_REG)
    SVN_ERR(b->walk_func(b->walk_baton, path, finfo, pool));

  return SVN_NO_ERROR;
}