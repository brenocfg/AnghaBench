#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_5__ {int /*<<< orphan*/  wrapped_node_baton; TYPE_3__* edit_baton; } ;
typedef  TYPE_2__ node_baton_t ;
struct TYPE_6__ {TYPE_1__* wrapped_editor; } ;
typedef  TYPE_3__ edit_baton_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_4__ {int /*<<< orphan*/ * (* absent_directory ) (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/ * stub1 (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
absent_directory(const char *path,
                 void *dir_baton,
                 apr_pool_t *pool)
{
  node_baton_t *db = dir_baton;
  edit_baton_t *eb = db->edit_baton;
  return eb->wrapped_editor->absent_directory(path, db->wrapped_node_baton,
                                              pool);
}