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
typedef  scalar_t__ svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct ev2_dir_baton {scalar_t__ base_revision; int /*<<< orphan*/  eb; } ;
struct change_node {scalar_t__ action; scalar_t__ deleting; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 scalar_t__ RESTRUCTURE_DELETE ; 
 scalar_t__ RESTRUCTURE_NONE ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int) ; 
 scalar_t__ SVN_IS_VALID_REVNUM (scalar_t__) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 struct change_node* locate_change (int /*<<< orphan*/ ,char const*) ; 
 char* map_to_repos_relpath (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
ev2_delete_entry(const char *path,
                 svn_revnum_t revision,
                 void *parent_baton,
                 apr_pool_t *scratch_pool)
{
  struct ev2_dir_baton *pb = parent_baton;
  svn_revnum_t base_revision;
  const char *relpath = map_to_repos_relpath(pb->eb, path, scratch_pool);
  struct change_node *change = locate_change(pb->eb, relpath);

  if (SVN_IS_VALID_REVNUM(revision))
    base_revision = revision;
  else
    base_revision = pb->base_revision;

  SVN_ERR_ASSERT(change->action == RESTRUCTURE_NONE);
  change->action = RESTRUCTURE_DELETE;

  SVN_ERR_ASSERT(!SVN_IS_VALID_REVNUM(change->deleting)
                 || change->deleting == base_revision);
  change->deleting = base_revision;

  return SVN_NO_ERROR;
}