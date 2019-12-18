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
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct ev2_edit_baton {TYPE_1__* exb; int /*<<< orphan*/  base_relpath; int /*<<< orphan*/  edit_pool; } ;
struct ev2_dir_baton {int /*<<< orphan*/  base_revision; int /*<<< orphan*/  path; struct ev2_edit_baton* eb; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_2__ {int /*<<< orphan*/  baton; int /*<<< orphan*/  (* start_edit ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 struct ev2_dir_baton* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  apr_pstrdup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
ev2_open_root(void *edit_baton,
              svn_revnum_t base_revision,
              apr_pool_t *result_pool,
              void **root_baton)
{
  struct ev2_dir_baton *db = apr_pcalloc(result_pool, sizeof(*db));
  struct ev2_edit_baton *eb = edit_baton;

  db->eb = eb;
  db->path = apr_pstrdup(eb->edit_pool, eb->base_relpath);
  db->base_revision = base_revision;

  *root_baton = db;

  if (eb->exb->start_edit)
    SVN_ERR(eb->exb->start_edit(eb->exb->baton, base_revision));

  return SVN_NO_ERROR;
}