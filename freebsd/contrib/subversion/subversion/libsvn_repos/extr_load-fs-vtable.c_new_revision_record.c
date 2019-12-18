#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ svn_revnum_t ;
struct TYPE_5__ {scalar_t__ old_revision; } ;
typedef  TYPE_1__ svn_repos_notify_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct revision_baton {scalar_t__ rev; scalar_t__ skipped; int /*<<< orphan*/  txn; int /*<<< orphan*/  txn_root; scalar_t__ rev_offset; } ;
struct parse_baton {scalar_t__ oldest_dumpstream_rev; int /*<<< orphan*/  notify_pool; int /*<<< orphan*/  notify_baton; int /*<<< orphan*/  (* notify_func ) (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  fs; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  scalar_t__ apr_int32_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_FS_TXN_CLIENT_DATE ; 
 int /*<<< orphan*/  SVN_IS_VALID_REVNUM (scalar_t__) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 struct revision_baton* make_revision_baton (int /*<<< orphan*/ *,struct parse_baton*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_begin_txn2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_txn_root (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_youngest_rev (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ ) ; 
 TYPE_1__* svn_repos_notify_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_repos_notify_load_skipped_rev ; 
 int /*<<< orphan*/  svn_repos_notify_load_txn_start ; 

__attribute__((used)) static svn_error_t *
new_revision_record(void **revision_baton,
                    apr_hash_t *headers,
                    void *parse_baton,
                    apr_pool_t *pool)
{
  struct parse_baton *pb = parse_baton;
  struct revision_baton *rb;
  svn_revnum_t head_rev;

  rb = make_revision_baton(headers, pb, pool);

  /* ### If we're filtering revisions, and this is one we've skipped,
     ### and we've skipped it because it has a revision number younger
     ### than the youngest in our acceptable range, then should we
     ### just bail out here? */
  /*
  if (rb->skipped && (rb->rev > pb->end_rev))
    return svn_error_createf(SVN_ERR_CEASE_INVOCATION, 0,
                             _("Finished processing acceptable load "
                               "revision range"));
  */

  SVN_ERR(svn_fs_youngest_rev(&head_rev, pb->fs, pool));

  /* FIXME: This is a lame fallback loading multiple segments of dump in
     several separate operations. It is highly susceptible to race conditions.
     Calculate the revision 'offset' for finding copyfrom sources.
     It might be positive or negative. */
  rb->rev_offset = (apr_int32_t) ((rb->rev) - (head_rev + 1));

  if ((rb->rev > 0) && (! rb->skipped))
    {
      /* Create a new fs txn. */
      SVN_ERR(svn_fs_begin_txn2(&(rb->txn), pb->fs, head_rev,
                                SVN_FS_TXN_CLIENT_DATE, pool));
      SVN_ERR(svn_fs_txn_root(&(rb->txn_root), rb->txn, pool));

      if (pb->notify_func)
        {
          /* ### TODO: Use proper scratch pool instead of pb->notify_pool */
          svn_repos_notify_t *notify = svn_repos_notify_create(
                                            svn_repos_notify_load_txn_start,
                                            pb->notify_pool);

          notify->old_revision = rb->rev;
          pb->notify_func(pb->notify_baton, notify, pb->notify_pool);
          svn_pool_clear(pb->notify_pool);
        }

      /* Stash the oldest "old" revision committed from the load stream. */
      if (!SVN_IS_VALID_REVNUM(pb->oldest_dumpstream_rev))
        pb->oldest_dumpstream_rev = rb->rev;
    }

  /* If we're skipping this revision, try to notify someone. */
  if (rb->skipped && pb->notify_func)
    {
      /* ### TODO: Use proper scratch pool instead of pb->notify_pool */
      svn_repos_notify_t *notify = svn_repos_notify_create(
                                        svn_repos_notify_load_skipped_rev,
                                        pb->notify_pool);

      notify->old_revision = rb->rev;
      pb->notify_func(pb->notify_baton, notify, pb->notify_pool);
      svn_pool_clear(pb->notify_pool);
    }

  /* If we're parsing revision 0, only the revision props are (possibly)
     interesting to us: when loading the stream into an empty
     filesystem, then we want new filesystem's revision 0 to have the
     same props.  Otherwise, we just ignore revision 0 in the stream. */

  *revision_baton = rb;
  return SVN_NO_ERROR;
}