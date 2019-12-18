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
typedef  int /*<<< orphan*/  svn_error_t ;
struct node_baton {int /*<<< orphan*/  wrapped_baton; int /*<<< orphan*/  filtered; struct edit_baton* edit_baton; } ;
struct edit_baton {TYPE_1__* wrapped_editor; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* close_directory ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
close_directory(void *dir_baton,
                apr_pool_t *pool)
{
  struct node_baton *db = dir_baton;
  struct edit_baton *eb = db->edit_baton;

  /* Don't close filtered directories. */
  if (! db->filtered)
    SVN_ERR(eb->wrapped_editor->close_directory(db->wrapped_baton, pool));

  return SVN_NO_ERROR;
}