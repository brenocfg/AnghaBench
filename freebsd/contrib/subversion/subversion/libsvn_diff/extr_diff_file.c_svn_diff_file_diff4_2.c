#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_diff_t ;
typedef  int /*<<< orphan*/  svn_diff_file_options_t ;
struct TYPE_5__ {int /*<<< orphan*/  pool; TYPE_1__* files; int /*<<< orphan*/  const* options; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_2__ svn_diff__file_baton_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_4__ {char const* path; } ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  svn_diff__file_vtable ; 
 int /*<<< orphan*/  svn_diff_diff4_2 (int /*<<< orphan*/ **,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ ) ; 

svn_error_t *
svn_diff_file_diff4_2(svn_diff_t **diff,
                      const char *original,
                      const char *modified,
                      const char *latest,
                      const char *ancestor,
                      const svn_diff_file_options_t *options,
                      apr_pool_t *pool)
{
  svn_diff__file_baton_t baton = { 0 };

  baton.options = options;
  baton.files[0].path = original;
  baton.files[1].path = modified;
  baton.files[2].path = latest;
  baton.files[3].path = ancestor;
  baton.pool = svn_pool_create(pool);

  SVN_ERR(svn_diff_diff4_2(diff, &baton, &svn_diff__file_vtable, pool));

  svn_pool_destroy(baton.pool);
  return SVN_NO_ERROR;
}