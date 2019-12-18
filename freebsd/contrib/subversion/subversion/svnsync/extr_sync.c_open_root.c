#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_6__ {void* edit_baton; int /*<<< orphan*/  wrapped_node_baton; } ;
typedef  TYPE_2__ node_baton_t ;
struct TYPE_7__ {int /*<<< orphan*/  called_open_root; int /*<<< orphan*/  wrapped_edit_baton; TYPE_1__* wrapped_editor; } ;
typedef  TYPE_3__ edit_baton_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_5__ {int /*<<< orphan*/  (* open_root ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_2__* apr_palloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
open_root(void *edit_baton,
          svn_revnum_t base_revision,
          apr_pool_t *pool,
          void **root_baton)
{
  edit_baton_t *eb = edit_baton;
  node_baton_t *dir_baton = apr_palloc(pool, sizeof(*dir_baton));

  SVN_ERR(eb->wrapped_editor->open_root(eb->wrapped_edit_baton,
                                        base_revision, pool,
                                        &dir_baton->wrapped_node_baton));

  eb->called_open_root = TRUE;
  dir_baton->edit_baton = edit_baton;
  *root_baton = dir_baton;

  return SVN_NO_ERROR;
}