#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;
typedef  struct TYPE_18__   TYPE_11__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_txdelta_stream_t ;
typedef  int /*<<< orphan*/  svn_stream_t ;
struct TYPE_20__ {TYPE_6__* fsap_data; } ;
typedef  TYPE_2__ svn_fs_t ;
struct TYPE_21__ {scalar_t__ type; scalar_t__ base_revision; scalar_t__ base_item_index; } ;
typedef  TYPE_3__ svn_fs_fs__rep_header_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_22__ {TYPE_1__* sfile; } ;
typedef  TYPE_4__ rep_state_t ;
struct TYPE_23__ {TYPE_11__* data_rep; } ;
typedef  TYPE_5__ node_revision_t ;
struct TYPE_24__ {int /*<<< orphan*/  fulltext_cache; } ;
typedef  TYPE_6__ fs_fs_data_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_19__ {int /*<<< orphan*/ * rfile; } ;
struct TYPE_18__ {scalar_t__ revision; scalar_t__ item_index; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  create_rep_state (TYPE_4__**,TYPE_3__**,int /*<<< orphan*/ *,TYPE_11__*,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * get_storaged_delta_stream (TYPE_4__*,TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_fs__close_revision_file (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_fs__get_contents (int /*<<< orphan*/ **,TYPE_2__*,TYPE_11__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_fs_fs__rep_delta ; 
 scalar_t__ svn_fs_fs__rep_self_delta ; 
 int /*<<< orphan*/ * svn_stream_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_txdelta2 (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_fs_fs__get_file_delta_stream(svn_txdelta_stream_t **stream_p,
                                 svn_fs_t *fs,
                                 node_revision_t *source,
                                 node_revision_t *target,
                                 apr_pool_t *pool)
{
  svn_stream_t *source_stream, *target_stream;
  rep_state_t *rep_state;
  svn_fs_fs__rep_header_t *rep_header;
  fs_fs_data_t *ffd = fs->fsap_data;

  /* Try a shortcut: if the target is stored as a delta against the source,
     then just use that delta.  However, prefer using the fulltext cache
     whenever that is available. */
  if (target->data_rep && (source || ! ffd->fulltext_cache))
    {
      /* Read target's base rep if any. */
      SVN_ERR(create_rep_state(&rep_state, &rep_header, NULL,
                                target->data_rep, fs, pool, pool));

      if (source && source->data_rep && target->data_rep)
        {
          /* If that matches source, then use this delta as is.
             Note that we want an actual delta here.  E.g. a self-delta would
             not be good enough. */
          if (rep_header->type == svn_fs_fs__rep_delta
              && rep_header->base_revision == source->data_rep->revision
              && rep_header->base_item_index == source->data_rep->item_index)
            {
              *stream_p = get_storaged_delta_stream(rep_state, target, pool);
              return SVN_NO_ERROR;
            }
        }
      else if (!source)
        {
          /* We want a self-delta. There is a fair chance that TARGET got
             added in this revision and is already stored in the requested
             format. */
          if (rep_header->type == svn_fs_fs__rep_self_delta)
            {
              *stream_p = get_storaged_delta_stream(rep_state, target, pool);
              return SVN_NO_ERROR;
            }
        }

      /* Don't keep file handles open for longer than necessary. */
      if (rep_state->sfile->rfile)
        {
          SVN_ERR(svn_fs_fs__close_revision_file(rep_state->sfile->rfile));
          rep_state->sfile->rfile = NULL;
        }
    }

  /* Read both fulltexts and construct a delta. */
  if (source)
    SVN_ERR(svn_fs_fs__get_contents(&source_stream, fs, source->data_rep,
                                    TRUE, pool));
  else
    source_stream = svn_stream_empty(pool);
  SVN_ERR(svn_fs_fs__get_contents(&target_stream, fs, target->data_rep,
                                  TRUE, pool));

  /* Because source and target stream will already verify their content,
   * there is no need to do this once more.  In particular if the stream
   * content is being fetched from cache. */
  svn_txdelta2(stream_p, source_stream, target_stream, FALSE, pool);

  return SVN_NO_ERROR;
}