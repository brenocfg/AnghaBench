#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ svn_node_kind_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct context {TYPE_1__* editor; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_2__ {int /*<<< orphan*/ * (* absent_file ) (char const*,void*,int /*<<< orphan*/ *) ;int /*<<< orphan*/ * (* absent_directory ) (char const*,void*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR_ASSERT (char const*) ; 
 int /*<<< orphan*/ * stub1 (char const*,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * stub2 (char const*,void*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_node_dir ; 

__attribute__((used)) static svn_error_t *
absent_file_or_dir(struct context *c,
                   void *dir_baton,
                   const char *edit_path,
                   svn_node_kind_t tgt_kind,
                   apr_pool_t *pool)
{
  SVN_ERR_ASSERT(edit_path);

  if (tgt_kind == svn_node_dir)
    return c->editor->absent_directory(edit_path, dir_baton, pool);
  else
    return c->editor->absent_file(edit_path, dir_baton, pool);
}