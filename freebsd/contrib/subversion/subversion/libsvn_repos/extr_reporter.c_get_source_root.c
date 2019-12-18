#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_fs_root_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_5__ {int /*<<< orphan*/ ** s_roots; int /*<<< orphan*/  pool; TYPE_1__* repos; } ;
typedef  TYPE_2__ report_baton_t ;
struct TYPE_4__ {int /*<<< orphan*/  fs; } ;

/* Variables and functions */
 int NUM_CACHED_SOURCE_ROOTS ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  svn_fs_close_root (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_revision_root (int /*<<< orphan*/ **,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ svn_fs_revision_root_revision (int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
get_source_root(report_baton_t *b, svn_fs_root_t **s_root, svn_revnum_t rev)
{
  int i;
  svn_fs_root_t *root, *prev = NULL;

  /* Look for the desired root in the cache, sliding all the unmatched
     entries backwards a slot to make room for the right one. */
  for (i = 0; i < NUM_CACHED_SOURCE_ROOTS; i++)
    {
      root = b->s_roots[i];
      b->s_roots[i] = prev;
      if (root && svn_fs_revision_root_revision(root) == rev)
        break;
      prev = root;
    }

  /* If we didn't find it, throw out the oldest root and open a new one. */
  if (i == NUM_CACHED_SOURCE_ROOTS)
    {
      if (prev)
        svn_fs_close_root(prev);
      SVN_ERR(svn_fs_revision_root(&root, b->repos->fs, rev, b->pool));
    }

  /* Assign the desired root to the first cache slot and hand it back. */
  b->s_roots[0] = root;
  *s_root = root;
  return SVN_NO_ERROR;
}