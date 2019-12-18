#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct ev2_file_baton {TYPE_1__* eb; int /*<<< orphan*/ * delta_base; int /*<<< orphan*/  base_revision; int /*<<< orphan*/  path; } ;
struct ev2_dir_baton {int /*<<< orphan*/  base_revision; TYPE_1__* eb; } ;
struct change_node {int /*<<< orphan*/  copyfrom_rev; void* copyfrom_path; int /*<<< orphan*/  kind; int /*<<< orphan*/  action; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_3__ {int /*<<< orphan*/  fetch_base_baton; int /*<<< orphan*/  (* fetch_base_func ) (int /*<<< orphan*/ **,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;int /*<<< orphan*/ * edit_pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  RESTRUCTURE_ADD ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 struct ev2_file_baton* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  apr_pstrdup (int /*<<< orphan*/ *,char const*) ; 
 struct change_node* locate_change (TYPE_1__*,char const*) ; 
 void* map_to_repos_relpath (TYPE_1__*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ **,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_node_file ; 

__attribute__((used)) static svn_error_t *
ev2_add_file(const char *path,
             void *parent_baton,
             const char *copyfrom_path,
             svn_revnum_t copyfrom_revision,
             apr_pool_t *result_pool,
             void **file_baton)
{
  /* ### fix this?  */
  apr_pool_t *scratch_pool = result_pool;
  struct ev2_file_baton *fb = apr_pcalloc(result_pool, sizeof(*fb));
  struct ev2_dir_baton *pb = parent_baton;
  const char *relpath = map_to_repos_relpath(pb->eb, path, scratch_pool);
  struct change_node *change = locate_change(pb->eb, relpath);

  /* ### assert that RESTRUCTURE is NONE or DELETE?  */
  change->action = RESTRUCTURE_ADD;
  change->kind = svn_node_file;

  fb->eb = pb->eb;
  fb->path = apr_pstrdup(result_pool, relpath);
  fb->base_revision = pb->base_revision;
  *file_baton = fb;

  if (!copyfrom_path)
    {
      /* Don't bother fetching the base, as in an add we don't have a base. */
      fb->delta_base = NULL;
    }
  else
    {
      /* A copy */

      change->copyfrom_path = map_to_repos_relpath(fb->eb, copyfrom_path,
                                                   fb->eb->edit_pool);
      change->copyfrom_rev = copyfrom_revision;

      SVN_ERR(fb->eb->fetch_base_func(&fb->delta_base,
                                      fb->eb->fetch_base_baton,
                                      change->copyfrom_path,
                                      change->copyfrom_rev,
                                      result_pool, scratch_pool));
    }

  return SVN_NO_ERROR;
}