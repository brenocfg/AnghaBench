#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {scalar_t__ len; } ;
typedef  TYPE_1__ svn_stringbuf_t ;
typedef  int /*<<< orphan*/  svn_stream_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_18__ {int /*<<< orphan*/  file_noderev_count; int /*<<< orphan*/  file_noderev_size; int /*<<< orphan*/  dir_noderev_count; int /*<<< orphan*/  dir_noderev_size; } ;
typedef  TYPE_2__ revision_info_t ;
struct TYPE_19__ {int ref_count; int /*<<< orphan*/  kind; int /*<<< orphan*/  revision; int /*<<< orphan*/  expanded_size; int /*<<< orphan*/  size; } ;
typedef  TYPE_3__ rep_stats_t ;
struct TYPE_20__ {int /*<<< orphan*/  fs; int /*<<< orphan*/  stats; } ;
typedef  TYPE_4__ query_t ;
struct TYPE_21__ {scalar_t__ kind; int /*<<< orphan*/  predecessor_id; int /*<<< orphan*/  created_path; scalar_t__ prop_rep; scalar_t__ data_rep; } ;
typedef  TYPE_5__ node_revision_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  add_change (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dir_property_rep ; 
 int /*<<< orphan*/  dir_rep ; 
 int /*<<< orphan*/  file_property_rep ; 
 int /*<<< orphan*/  file_rep ; 
 int /*<<< orphan*/  parse_dir (TYPE_4__*,TYPE_5__*,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parse_representation (TYPE_3__**,TYPE_4__*,scalar_t__,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_fs__fixup_expanded_size (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_fs__read_noderev (TYPE_5__**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_fs__use_log_addressing (int /*<<< orphan*/ ) ; 
 scalar_t__ svn_node_dir ; 
 int /*<<< orphan*/ * svn_stream_from_stringbuf (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
read_noderev(query_t *query,
             svn_stringbuf_t *noderev_str,
             revision_info_t *revision_info,
             apr_pool_t *result_pool,
             apr_pool_t *scratch_pool)
{
  rep_stats_t *text = NULL;
  rep_stats_t *props = NULL;
  node_revision_t *noderev;

  svn_stream_t *stream = svn_stream_from_stringbuf(noderev_str, scratch_pool);
  SVN_ERR(svn_fs_fs__read_noderev(&noderev, stream, scratch_pool,
                                  scratch_pool));
  SVN_ERR(svn_fs_fs__fixup_expanded_size(query->fs, noderev->data_rep,
                                         scratch_pool));
  SVN_ERR(svn_fs_fs__fixup_expanded_size(query->fs, noderev->prop_rep,
                                         scratch_pool));

  if (noderev->data_rep)
    {
      SVN_ERR(parse_representation(&text, query,
                                   noderev->data_rep, revision_info,
                                   result_pool, scratch_pool));

      /* if we are the first to use this rep, mark it as "text rep" */
      if (++text->ref_count == 1)
        text->kind = noderev->kind == svn_node_dir ? dir_rep : file_rep;
    }

  if (noderev->prop_rep)
    {
      SVN_ERR(parse_representation(&props, query,
                                   noderev->prop_rep, revision_info,
                                   result_pool, scratch_pool));

      /* if we are the first to use this rep, mark it as "prop rep" */
      if (++props->ref_count == 1)
        props->kind = noderev->kind == svn_node_dir ? dir_property_rep
                                                    : file_property_rep;
    }

  /* record largest changes */
  if (text && text->ref_count == 1)
    add_change(query->stats, text->size, text->expanded_size, text->revision,
               noderev->created_path, text->kind, !noderev->predecessor_id);
  if (props && props->ref_count == 1)
    add_change(query->stats, props->size, props->expanded_size,
               props->revision, noderev->created_path, props->kind,
               !noderev->predecessor_id);

  /* if this is a directory and has not been processed, yet, read and
   * process it recursively */
  if (   noderev->kind == svn_node_dir && text && text->ref_count == 1
      && !svn_fs_fs__use_log_addressing(query->fs))
    SVN_ERR(parse_dir(query, noderev, revision_info, result_pool,
                      scratch_pool));

  /* update stats */
  if (noderev->kind == svn_node_dir)
    {
      revision_info->dir_noderev_size += noderev_str->len;
      revision_info->dir_noderev_count++;
    }
  else
    {
      revision_info->file_noderev_size += noderev_str->len;
      revision_info->file_noderev_count++;
    }

  return SVN_NO_ERROR;
}