#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_1__* vtable; } ;
typedef  TYPE_2__ svn_fs_root_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_9__ {int /*<<< orphan*/  (* merge ) (char const**,TYPE_2__*,char const*,TYPE_2__*,char const*,TYPE_2__*,char const*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (char const**,TYPE_2__*,char const*,TYPE_2__*,char const*,TYPE_2__*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 

svn_error_t *
svn_fs_merge(const char **conflict_p, svn_fs_root_t *source_root,
             const char *source_path, svn_fs_root_t *target_root,
             const char *target_path, svn_fs_root_t *ancestor_root,
             const char *ancestor_path, apr_pool_t *pool)
{
  return svn_error_trace(target_root->vtable->merge(conflict_p,
                                                    source_root, source_path,
                                                    target_root, target_path,
                                                    ancestor_root,
                                                    ancestor_path, pool));
}