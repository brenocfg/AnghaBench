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
typedef  scalar_t__ svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_3__ {scalar_t__ revision; } ;
typedef  TYPE_1__ svn_commit_info_t ;
struct revision_baton {scalar_t__ rev; struct parse_baton* pb; } ;
struct parse_baton {scalar_t__ last_rev_mapped; int /*<<< orphan*/  rev_map; int /*<<< orphan*/  quiet; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ SVN_INVALID_REVNUM ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  set_revision_mapping (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  svn_cmdline_printf (int /*<<< orphan*/ *,char*,scalar_t__) ; 

__attribute__((used)) static svn_error_t *
commit_callback(const svn_commit_info_t *commit_info,
                void *baton,
                apr_pool_t *pool)
{
  struct revision_baton *rb = baton;
  struct parse_baton *pb = rb->pb;

  /* ### Don't print directly; generate a notification. */
  if (! pb->quiet)
    SVN_ERR(svn_cmdline_printf(pool, "* Loaded revision %ld.\n",
                               commit_info->revision));

  /* Add the mapping of the dumpstream revision to the committed revision. */
  set_revision_mapping(pb->rev_map, rb->rev, commit_info->revision);

  /* If the incoming dump stream has non-contiguous revisions (e.g. from
     using svndumpfilter --drop-empty-revs without --renumber-revs) then
     we must account for the missing gaps in PB->REV_MAP.  Otherwise we
     might not be able to map all mergeinfo source revisions to the correct
     revisions in the target repos. */
  if ((pb->last_rev_mapped != SVN_INVALID_REVNUM)
      && (rb->rev != pb->last_rev_mapped + 1))
    {
      svn_revnum_t i;

      for (i = pb->last_rev_mapped + 1; i < rb->rev; i++)
        {
          set_revision_mapping(pb->rev_map, i, pb->last_rev_mapped);
        }
    }

  /* Update our "last revision mapped". */
  pb->last_rev_mapped = rb->rev;

  return SVN_NO_ERROR;
}