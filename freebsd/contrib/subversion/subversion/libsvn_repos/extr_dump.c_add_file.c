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
typedef  scalar_t__ svn_boolean_t ;
struct edit_baton {scalar_t__ notify_func; scalar_t__ check_normalization; scalar_t__ verify; } ;
struct dir_baton {int /*<<< orphan*/  check_name_collision; int /*<<< orphan*/  deleted_entries; struct edit_baton* edit_baton; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 scalar_t__ ARE_VALID_COPY_ARGS (char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_INVALID_REVNUM ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  dump_node (struct edit_baton*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* svn_hash_gets (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  svn_hash_sets (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_node_action_add ; 
 int /*<<< orphan*/  svn_node_action_replace ; 
 int /*<<< orphan*/  svn_node_file ; 

__attribute__((used)) static svn_error_t *
add_file(const char *path,
         void *parent_baton,
         const char *copyfrom_path,
         svn_revnum_t copyfrom_rev,
         apr_pool_t *pool,
         void **file_baton)
{
  struct dir_baton *pb = parent_baton;
  struct edit_baton *eb = pb->edit_baton;
  void *was_deleted;
  svn_boolean_t is_copy = FALSE;

  /* This might be a replacement -- is the path already deleted? */
  was_deleted = svn_hash_gets(pb->deleted_entries, path);

  /* Detect add-with-history. */
  is_copy = ARE_VALID_COPY_ARGS(copyfrom_path, copyfrom_rev);

  /* Dump the node. */
  SVN_ERR(dump_node(eb, path,
                    svn_node_file,
                    was_deleted ? svn_node_action_replace : svn_node_action_add,
                    is_copy,
                    is_copy ? copyfrom_path : NULL,
                    is_copy ? copyfrom_rev : SVN_INVALID_REVNUM,
                    pool));

  if (was_deleted)
    /* delete the path, it's now been dumped. */
    svn_hash_sets(pb->deleted_entries, path, NULL);

  /* Check for normalized name clashes, but only if this is actually a
     new name in the parent, not a replacement. */
  if (!was_deleted && eb->verify && eb->check_normalization && eb->notify_func)
    {
      pb->check_name_collision = TRUE;
    }

  *file_baton = NULL;  /* muhahahaha */
  return SVN_NO_ERROR;
}