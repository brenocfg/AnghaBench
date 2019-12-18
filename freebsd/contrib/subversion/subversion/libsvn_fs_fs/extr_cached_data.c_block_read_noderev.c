#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_stream_t ;
struct TYPE_14__ {TYPE_5__* fsap_data; } ;
typedef  TYPE_2__ svn_fs_t ;
typedef  int /*<<< orphan*/  svn_fs_fs__revision_file_t ;
struct TYPE_13__ {int /*<<< orphan*/  number; int /*<<< orphan*/  revision; } ;
struct TYPE_15__ {TYPE_1__ item; } ;
typedef  TYPE_3__ svn_fs_fs__p2l_entry_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
struct TYPE_16__ {int /*<<< orphan*/  second; int /*<<< orphan*/  revision; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_4__ pair_cache_key_t ;
typedef  int /*<<< orphan*/  node_revision_t ;
struct TYPE_17__ {scalar_t__ node_revision_cache; } ;
typedef  TYPE_5__ fs_fs_data_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  fixup_node_revision (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_item (int /*<<< orphan*/ **,TYPE_2__*,int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_cache__has_key (scalar_t__*,scalar_t__,TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_cache__set (scalar_t__,TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_fs__read_noderev (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
block_read_noderev(node_revision_t **noderev_p,
                   svn_fs_t *fs,
                   svn_fs_fs__revision_file_t *rev_file,
                   svn_fs_fs__p2l_entry_t *entry,
                   svn_boolean_t must_read,
                   apr_pool_t *result_pool,
                   apr_pool_t *scratch_pool)
{
  fs_fs_data_t *ffd = fs->fsap_data;
  svn_stream_t *stream;

  pair_cache_key_t key = { 0 };
  key.revision = entry->item.revision;
  key.second = entry->item.number;

  if (!must_read && !ffd->node_revision_cache)
    return SVN_NO_ERROR;

  /* already in cache? */
  if (!must_read && ffd->node_revision_cache)
    {
      svn_boolean_t is_cached;
      SVN_ERR(svn_cache__has_key(&is_cached, ffd->node_revision_cache,
                                 &key, scratch_pool));
      if (is_cached)
        return SVN_NO_ERROR;
    }

  SVN_ERR(read_item(&stream, fs, rev_file, entry, scratch_pool));

  /* read node rev from revision file */
  SVN_ERR(svn_fs_fs__read_noderev(noderev_p, stream,
                                  result_pool, scratch_pool));
  SVN_ERR(fixup_node_revision(fs, *noderev_p, scratch_pool));

  if (ffd->node_revision_cache)
    SVN_ERR(svn_cache__set(ffd->node_revision_cache, &key, *noderev_p,
                           scratch_pool));

  return SVN_NO_ERROR;
}