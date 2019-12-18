#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ svn_revnum_t ;
typedef  scalar_t__ svn_node_kind_t ;
struct TYPE_12__ {TYPE_4__* fsap_data; } ;
typedef  TYPE_1__ svn_fs_t ;
struct TYPE_13__ {scalar_t__ rev; } ;
typedef  TYPE_2__ svn_fs_root_t ;
typedef  int /*<<< orphan*/  svn_fs_id_t ;
struct TYPE_14__ {scalar_t__ kind; int /*<<< orphan*/ * id; } ;
typedef  TYPE_3__ svn_fs_dirent_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct txn_pred_id_args {char const* txn_id; int is_dir; int pred_count; int /*<<< orphan*/  const* base_id; int /*<<< orphan*/  const* tgt_id; int /*<<< orphan*/ * pred_id; int /*<<< orphan*/ * pool; int /*<<< orphan*/  const* id; } ;
struct txn_pred_count_args {char const* txn_id; int is_dir; int pred_count; int /*<<< orphan*/  const* base_id; int /*<<< orphan*/  const* tgt_id; int /*<<< orphan*/ * pred_id; int /*<<< orphan*/ * pool; int /*<<< orphan*/  const* id; } ;
struct txn_deltify_args {char const* txn_id; int is_dir; int pred_count; int /*<<< orphan*/  const* base_id; int /*<<< orphan*/  const* tgt_id; int /*<<< orphan*/ * pred_id; int /*<<< orphan*/ * pool; int /*<<< orphan*/  const* id; } ;
struct TYPE_15__ {scalar_t__ format; } ;
typedef  TYPE_4__ base_fs_data_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_hash_index_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SVN_ERR_FS_CORRUPT ; 
 scalar_t__ SVN_FS_BASE__MIN_FORWARD_DELTAS_FORMAT ; 
 scalar_t__ SVN_FS_BASE__MIN_MISCELLANY_FORMAT ; 
 int /*<<< orphan*/  SVN_FS_BASE__MISC_FORWARD_DELTA_UPGRADE ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/ * apr_hash_first (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_hash_this (int /*<<< orphan*/ *,void const**,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/ * base_check_path (scalar_t__*,TYPE_2__*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * base_dir_entries (int /*<<< orphan*/ **,TYPE_2__*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * base_node_id (int /*<<< orphan*/  const**,TYPE_2__*,char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_base__id_txn_id (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * svn_fs_base__miscellaneous_get (char const**,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_fs_base__retry_txn (TYPE_1__*,int /*<<< orphan*/ ,struct txn_pred_id_args*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* svn_fspath__join (char const*,void const*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_node_dir ; 
 scalar_t__ svn_node_unknown ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_revnum_parse (scalar_t__*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  txn_body_pred_count ; 
 int /*<<< orphan*/  txn_body_pred_id ; 
 int /*<<< orphan*/  txn_body_txn_deltify ; 

__attribute__((used)) static svn_error_t *
deltify_mutable(svn_fs_t *fs,
                svn_fs_root_t *root,
                const char *path,
                const svn_fs_id_t *node_id,
                svn_node_kind_t kind,
                const char *txn_id,
                apr_pool_t *pool)
{
  const svn_fs_id_t *id = node_id;
  apr_hash_t *entries = NULL;
  struct txn_deltify_args td_args;
  base_fs_data_t *bfd = fs->fsap_data;

  /* Get the ID for PATH under ROOT if it wasn't provided. */
  if (! node_id)
    SVN_ERR(base_node_id(&id, root, path, pool));

  /* Check for mutability.  Not mutable?  Go no further.  This is safe
     to do because for items in the tree to be mutable, their parent
     dirs must also be mutable.  Therefore, if a directory is not
     mutable under TXN_ID, its children cannot be.  */
  if (strcmp(svn_fs_base__id_txn_id(id), txn_id))
    return SVN_NO_ERROR;

  /* Is this a directory?  */
  if (kind == svn_node_unknown)
    SVN_ERR(base_check_path(&kind, root, path, pool));

  /* If this is a directory, read its entries.  */
  if (kind == svn_node_dir)
    SVN_ERR(base_dir_entries(&entries, root, path, pool));

  /* If there are entries, recurse on 'em.  */
  if (entries)
    {
      apr_pool_t *subpool = svn_pool_create(pool);
      apr_hash_index_t *hi;

      for (hi = apr_hash_first(pool, entries); hi; hi = apr_hash_next(hi))
        {
          /* KEY will be the entry name, VAL the dirent */
          const void *key;
          void *val;
          svn_fs_dirent_t *entry;
          svn_pool_clear(subpool);
          apr_hash_this(hi, &key, NULL, &val);
          entry = val;
          SVN_ERR(deltify_mutable(fs, root,
                                  svn_fspath__join(path, key, subpool),
                                  entry->id, entry->kind, txn_id, subpool));
        }

      svn_pool_destroy(subpool);
    }

  /* Index ID's data checksum. */
  td_args.txn_id = txn_id;
  td_args.tgt_id = id;
  td_args.base_id = NULL;
  td_args.is_dir = (kind == svn_node_dir);
  SVN_ERR(svn_fs_base__retry_txn(fs, txn_body_txn_deltify, &td_args,
                                 TRUE, pool));

  /* Finally, deltify old data against this node. */
  {
    /* Prior to 1.6, we use the following algorithm to deltify nodes:

       Redeltify predecessor node-revisions of the one we added.  The
       idea is to require at most 2*lg(N) deltas to be applied to get
       to any node-revision in a chain of N predecessors.  We do this
       using a technique derived from skip lists:

          - Always redeltify the immediate parent

          - If the number of predecessors is divisible by 2,
              redeltify the revision two predecessors back

          - If the number of predecessors is divisible by 4,
              redeltify the revision four predecessors back

       ... and so on.

       That's the theory, anyway.  Unfortunately, if we strictly
       follow that theory we get a bunch of overhead up front and no
       great benefit until the number of predecessors gets large.  So,
       stop at redeltifying the parent if the number of predecessors
       is less than 32, and also skip the second level (redeltifying
       two predecessors back), since that doesn't help much.  Also,
       don't redeltify the oldest node-revision; it's potentially
       expensive and doesn't help retrieve any other revision.
       (Retrieving the oldest node-revision will still be fast, just
       not as blindingly so.)

       For 1.6 and beyond, we just deltify the current node against its
       predecessors, using skip deltas similar to the way FSFS does.  */

    int pred_count;
    const svn_fs_id_t *pred_id;
    struct txn_pred_count_args tpc_args;
    apr_pool_t *subpools[2];
    int active_subpool = 0;
    svn_revnum_t forward_delta_rev = 0;

    tpc_args.id = id;
    SVN_ERR(svn_fs_base__retry_txn(fs, txn_body_pred_count, &tpc_args,
                                   TRUE, pool));
    pred_count = tpc_args.pred_count;

    /* If nothing to deltify, then we're done. */
    if (pred_count == 0)
      return SVN_NO_ERROR;

    subpools[0] = svn_pool_create(pool);
    subpools[1] = svn_pool_create(pool);

    /* If we support the 'miscellaneous' table, check it to see if
       there is a point in time before which we don't want to do
       deltification. */
    /* ### FIXME:  I think this is an unnecessary restriction.  We
       ### should be able to do something meaningful for most
       ### deltification requests -- what that is depends on the
       ### directory of the deltas for that revision, though. */
    if (bfd->format >= SVN_FS_BASE__MIN_MISCELLANY_FORMAT)
      {
        const char *val;
        SVN_ERR(svn_fs_base__miscellaneous_get
                (&val, fs, SVN_FS_BASE__MISC_FORWARD_DELTA_UPGRADE, pool));
        if (val)
          SVN_ERR(svn_revnum_parse(&forward_delta_rev, val, NULL));
      }

    if (bfd->format >= SVN_FS_BASE__MIN_FORWARD_DELTAS_FORMAT
          && forward_delta_rev <= root->rev)
      {
        /**** FORWARD DELTA STORAGE ****/

        /* Decide which predecessor to deltify against.  Flip the rightmost '1'
           bit of the predecessor count to determine which file rev (counting
           from 0) we want to use.  (To see why count & (count - 1) unsets the
           rightmost set bit, think about how you decrement a binary number. */
        pred_count = pred_count & (pred_count - 1);

        /* Walk back a number of predecessors equal to the difference between
           pred_count and the original predecessor count.  (For example, if
           the node has ten predecessors and we want the eighth node, walk back
           two predecessors. */
        pred_id = id;

        /* We need to use two alternating pools because the id used in the
           call to txn_body_pred_id is allocated by the previous inner
           loop iteration.  If we would clear the pool each iteration we
           would free the previous result.  */
        while ((pred_count++) < tpc_args.pred_count)
          {
            struct txn_pred_id_args tpi_args;

            active_subpool = !active_subpool;
            svn_pool_clear(subpools[active_subpool]);

            tpi_args.id = pred_id;
            tpi_args.pool = subpools[active_subpool];
            SVN_ERR(svn_fs_base__retry_txn(fs, txn_body_pred_id, &tpi_args,
                                           FALSE, subpools[active_subpool]));
            pred_id = tpi_args.pred_id;

            if (pred_id == NULL)
              return svn_error_create
                (SVN_ERR_FS_CORRUPT, 0,
                 _("Corrupt DB: faulty predecessor count"));

          }

        /* Finally, do the deltification. */
        td_args.txn_id = txn_id;
        td_args.tgt_id = id;
        td_args.base_id = pred_id;
        td_args.is_dir = (kind == svn_node_dir);
        SVN_ERR(svn_fs_base__retry_txn(fs, txn_body_txn_deltify, &td_args,
                                       TRUE, subpools[active_subpool]));
      }
    else
      {
        int nlevels, lev, count;

        /**** REVERSE DELTA STORAGE ****/

        /* Decide how many predecessors to redeltify.  To save overhead,
           don't redeltify anything but the immediate predecessor if there
           are less than 32 predecessors. */
        nlevels = 1;
        if (pred_count >= 32)
          {
            while (pred_count % 2 == 0)
              {
                pred_count /= 2;
                nlevels++;
              }

            /* Don't redeltify the oldest revision. */
            if (1 << (nlevels - 1) == pred_count)
              nlevels--;
          }

        /* Redeltify the desired number of predecessors. */
        count = 0;
        pred_id = id;

        /* We need to use two alternating pools because the id used in the
           call to txn_body_pred_id is allocated by the previous inner
           loop iteration.  If we would clear the pool each iteration we
           would free the previous result.  */
        for (lev = 0; lev < nlevels; lev++)
          {
            /* To save overhead, skip the second level (that is, never
               redeltify the node-revision two predecessors back). */
            if (lev == 1)
              continue;

            /* Note that COUNT is not reset between levels, and neither is
               PREDNODE; we just keep counting from where we were up to
               where we're supposed to get. */
            while (count < (1 << lev))
              {
                struct txn_pred_id_args tpi_args;

                active_subpool = !active_subpool;
                svn_pool_clear(subpools[active_subpool]);

                tpi_args.id = pred_id;
                tpi_args.pool = subpools[active_subpool];
                SVN_ERR(svn_fs_base__retry_txn(fs, txn_body_pred_id,
                                               &tpi_args, FALSE,
                                               subpools[active_subpool]));
                pred_id = tpi_args.pred_id;

                if (pred_id == NULL)
                  return svn_error_create
                    (SVN_ERR_FS_CORRUPT, 0,
                     _("Corrupt DB: faulty predecessor count"));

                count++;
              }

            /* Finally, do the deltification. */
            td_args.txn_id = NULL;  /* Don't require mutable reps */
            td_args.tgt_id = pred_id;
            td_args.base_id = id;
            td_args.is_dir = (kind == svn_node_dir);
            SVN_ERR(svn_fs_base__retry_txn(fs, txn_body_txn_deltify, &td_args,
                                           TRUE, subpools[active_subpool]));

          }
      }

    svn_pool_destroy(subpools[0]);
    svn_pool_destroy(subpools[1]);
  }

  return SVN_NO_ERROR;
}