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
struct edit_baton_t {char* target; TYPE_1__* processor; int /*<<< orphan*/  revnum; int /*<<< orphan*/  depth; void* root_opened; } ;
struct dir_baton_t {void* skip; int /*<<< orphan*/  pool; void* right_src; void* left_src; int /*<<< orphan*/  skip_children; int /*<<< orphan*/  pdb; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* dir_opened ) (int /*<<< orphan*/ *,void**,int /*<<< orphan*/ *,char*,void*,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_INVALID_REVNUM ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 void* TRUE ; 
 struct dir_baton_t* make_dir_baton (char*,int /*<<< orphan*/ *,struct edit_baton_t*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,void**,int /*<<< orphan*/ *,char*,void*,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* svn_diff__source_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
open_root(void *edit_baton,
          svn_revnum_t base_revision,
          apr_pool_t *dir_pool,
          void **root_baton)
{
  struct edit_baton_t *eb = edit_baton;
  struct dir_baton_t *db;

  eb->root_opened = TRUE;
  db = make_dir_baton("", NULL, eb, FALSE, eb->depth, dir_pool);
  *root_baton = db;

  if (eb->target[0] == '\0')
    {
      db->left_src = svn_diff__source_create(eb->revnum, db->pool);
      db->right_src = svn_diff__source_create(SVN_INVALID_REVNUM, db->pool);

      SVN_ERR(eb->processor->dir_opened(&db->pdb, &db->skip,
                                        &db->skip_children,
                                        "",
                                        db->left_src,
                                        db->right_src,
                                        NULL /* copyfrom_source */,
                                        NULL /* parent_baton */,
                                        eb->processor,
                                        db->pool, db->pool));
    }
  else
    db->skip = TRUE; /* Skip this, but not the children */

  return SVN_NO_ERROR;
}