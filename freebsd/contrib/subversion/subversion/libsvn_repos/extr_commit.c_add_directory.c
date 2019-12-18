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
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * add_file_or_directory (char const*,void*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 

__attribute__((used)) static svn_error_t *
add_directory(const char *path,
              void *parent_baton,
              const char *copy_path,
              svn_revnum_t copy_revision,
              apr_pool_t *pool,
              void **child_baton)
{
  return add_file_or_directory(path, parent_baton, copy_path, copy_revision,
                               TRUE /* is_dir */, pool, child_baton);
}