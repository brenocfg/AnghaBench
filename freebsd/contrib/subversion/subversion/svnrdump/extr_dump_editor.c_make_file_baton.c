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
struct file_baton {int /*<<< orphan*/  action; int /*<<< orphan*/  copyfrom_rev; int /*<<< orphan*/ * copyfrom_path; int /*<<< orphan*/  is_copy; void* deleted_props; void* props; int /*<<< orphan*/  repos_relpath; int /*<<< orphan*/ * pool; int /*<<< orphan*/  eb; } ;
struct dir_baton {int /*<<< orphan*/  eb; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_INVALID_REVNUM ; 
 void* apr_hash_make (int /*<<< orphan*/ *) ; 
 struct file_baton* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  svn_node_action_change ; 
 int /*<<< orphan*/  svn_relpath_canonicalize (char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct file_baton *
make_file_baton(const char *path,
                struct dir_baton *pb,
                apr_pool_t *pool)
{
  struct file_baton *new_fb = apr_pcalloc(pool, sizeof(*new_fb));

  new_fb->eb = pb->eb;
  new_fb->pool = pool;
  new_fb->repos_relpath = svn_relpath_canonicalize(path, pool);
  new_fb->props = apr_hash_make(pool);
  new_fb->deleted_props = apr_hash_make(pool);
  new_fb->is_copy = FALSE;
  new_fb->copyfrom_path = NULL;
  new_fb->copyfrom_rev = SVN_INVALID_REVNUM;
  new_fb->action = svn_node_action_change;

  return new_fb;
}