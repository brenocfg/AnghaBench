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
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct file_baton {int /*<<< orphan*/  action; int /*<<< orphan*/  is_copy; int /*<<< orphan*/  copyfrom_rev; int /*<<< orphan*/  pool; int /*<<< orphan*/  copyfrom_path; } ;
struct dir_baton {int /*<<< orphan*/  deleted_entries; int /*<<< orphan*/  eb; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 scalar_t__ ARE_VALID_COPY_ARGS (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  dump_pending_dir (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct file_baton* make_file_baton (char const*,struct dir_baton*,int /*<<< orphan*/ *) ; 
 void* svn_hash_gets (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  svn_hash_sets (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_node_action_add ; 
 int /*<<< orphan*/  svn_node_action_replace ; 
 int /*<<< orphan*/  svn_relpath_canonicalize (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
add_file(const char *path,
         void *parent_baton,
         const char *copyfrom_path,
         svn_revnum_t copyfrom_rev,
         apr_pool_t *pool,
         void **file_baton)
{
  struct dir_baton *pb = parent_baton;
  struct file_baton *fb;
  void *was_deleted;

  SVN_ERR(dump_pending_dir(pb->eb, pool));

  /* Make the file baton. */
  fb = make_file_baton(path, pb, pool);

  /* This might be a replacement -- is the path already deleted? */
  was_deleted = svn_hash_gets(pb->deleted_entries, path);

  /* Detect add-with-history. */
  if (ARE_VALID_COPY_ARGS(copyfrom_path, copyfrom_rev))
    {
      fb->copyfrom_path = svn_relpath_canonicalize(copyfrom_path, fb->pool);
      fb->copyfrom_rev = copyfrom_rev;
      fb->is_copy = TRUE;
    }
  fb->action = was_deleted ? svn_node_action_replace : svn_node_action_add;

  /* Delete the path, it's now been dumped. */
  if (was_deleted)
    svn_hash_sets(pb->deleted_entries, path, NULL);

  *file_baton = fb;
  return SVN_NO_ERROR;
}