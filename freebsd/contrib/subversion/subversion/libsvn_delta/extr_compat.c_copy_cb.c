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
typedef  void* svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct editor_baton {int /*<<< orphan*/  fetch_kind_baton; int /*<<< orphan*/  (* fetch_kind_func ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  edit_pool; int /*<<< orphan*/  changes; } ;
struct change_node {void* copyfrom_rev; int /*<<< orphan*/  copyfrom_path; int /*<<< orphan*/  kind; void* deleting; int /*<<< orphan*/  action; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  RESTRUCTURE_ADD ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  apr_pstrdup (int /*<<< orphan*/ ,char const*) ; 
 struct change_node* insert_change (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
copy_cb(void *baton,
        const char *src_relpath,
        svn_revnum_t src_revision,
        const char *dst_relpath,
        svn_revnum_t replaces_rev,
        apr_pool_t *scratch_pool)
{
  struct editor_baton *eb = baton;
  struct change_node *change = insert_change(dst_relpath, eb->changes);

  change->action = RESTRUCTURE_ADD;
  /* change->kind = svn_node_unknown;  */
  change->deleting = replaces_rev;
  change->copyfrom_path = apr_pstrdup(eb->edit_pool, src_relpath);
  change->copyfrom_rev = src_revision;

  /* We need the source's kind to know whether to call add_directory()
     or add_file() later on.  */
  SVN_ERR(eb->fetch_kind_func(&change->kind, eb->fetch_kind_baton,
                              change->copyfrom_path,
                              change->copyfrom_rev,
                              scratch_pool));

  /* Note: this node may later have alter_*() called on it.  */

  return SVN_NO_ERROR;
}