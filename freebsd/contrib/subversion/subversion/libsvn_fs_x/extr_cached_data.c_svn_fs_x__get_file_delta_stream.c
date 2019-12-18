#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_txdelta_stream_t ;
typedef  int /*<<< orphan*/  svn_stream_t ;
struct TYPE_16__ {scalar_t__ type; scalar_t__ base_revision; scalar_t__ base_item_index; } ;
typedef  TYPE_3__ svn_fs_x__rep_header_t ;
struct TYPE_17__ {TYPE_8__* data_rep; } ;
typedef  TYPE_4__ svn_fs_x__noderev_t ;
typedef  int /*<<< orphan*/  svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_18__ {TYPE_2__* sfile; } ;
typedef  TYPE_5__ rep_state_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_14__ {scalar_t__ number; int /*<<< orphan*/  change_set; } ;
struct TYPE_19__ {TYPE_1__ id; } ;
struct TYPE_15__ {int /*<<< orphan*/ * rfile; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  create_rep_state (TYPE_5__**,TYPE_3__**,int /*<<< orphan*/ *,TYPE_8__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * get_storaged_delta_stream (TYPE_5__*,TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__close_revision_file (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__get_contents (int /*<<< orphan*/ **,int /*<<< orphan*/ *,TYPE_8__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_fs_x__get_revnum (int /*<<< orphan*/ ) ; 
 scalar_t__ svn_fs_x__rep_delta ; 
 scalar_t__ svn_fs_x__rep_self_delta ; 
 int /*<<< orphan*/ * svn_stream_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_txdelta2 (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_fs_x__get_file_delta_stream(svn_txdelta_stream_t **stream_p,
                                svn_fs_t *fs,
                                svn_fs_x__noderev_t *source,
                                svn_fs_x__noderev_t *target,
                                apr_pool_t *result_pool,
                                apr_pool_t *scratch_pool)
{
  svn_stream_t *source_stream, *target_stream;
  rep_state_t *rep_state;
  svn_fs_x__rep_header_t *rep_header;

  /* Try a shortcut: if the target is stored as a delta against the source,
     then just use that delta.  However, prefer using the fulltext cache
     whenever that is available. */
  if (target->data_rep && source)
    {
      /* Read target's base rep if any. */
      SVN_ERR(create_rep_state(&rep_state, &rep_header, NULL,
                               target->data_rep, fs, result_pool,
                               scratch_pool));

      /* Try a shortcut: if the target is stored as a delta against the source,
         then just use that delta. */
      if (source && source->data_rep && target->data_rep)
        {
          /* If that matches source, then use this delta as is.
             Note that we want an actual delta here.  E.g. a self-delta would
             not be good enough. */
          if (rep_header->type == svn_fs_x__rep_delta
              && rep_header->base_revision
                 == svn_fs_x__get_revnum(source->data_rep->id.change_set)
              && rep_header->base_item_index == source->data_rep->id.number)
            {
              *stream_p = get_storaged_delta_stream(rep_state, target,
                                                    result_pool);
              return SVN_NO_ERROR;
            }
        }
      else if (!source)
        {
          /* We want a self-delta. There is a fair chance that TARGET got
             added in this revision and is already stored in the requested
             format. */
          if (rep_header->type == svn_fs_x__rep_self_delta)
            {
              *stream_p = get_storaged_delta_stream(rep_state, target,
                                                    result_pool);
              return SVN_NO_ERROR;
            }
        }

      /* Don't keep file handles open for longer than necessary. */
      if (rep_state->sfile->rfile)
        {
          SVN_ERR(svn_fs_x__close_revision_file(rep_state->sfile->rfile));
          rep_state->sfile->rfile = NULL;
        }
    }

  /* Read both fulltexts and construct a delta. */
  if (source)
    SVN_ERR(svn_fs_x__get_contents(&source_stream, fs, source->data_rep,
                                   TRUE, result_pool));
  else
    source_stream = svn_stream_empty(result_pool);

  SVN_ERR(svn_fs_x__get_contents(&target_stream, fs, target->data_rep,
                                 TRUE, result_pool));

  /* Because source and target stream will already verify their content,
   * there is no need to do this once more.  In particular if the stream
   * content is being fetched from cache. */
  svn_txdelta2(stream_p, source_stream, target_stream, FALSE, result_pool);

  return SVN_NO_ERROR;
}