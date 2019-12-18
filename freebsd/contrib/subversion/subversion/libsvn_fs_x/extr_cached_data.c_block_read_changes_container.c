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
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_fs_x__revision_file_t ;
struct TYPE_14__ {int /*<<< orphan*/  second; int /*<<< orphan*/  revision; } ;
typedef  TYPE_2__ svn_fs_x__pair_cache_key_t ;
struct TYPE_15__ {int /*<<< orphan*/  offset; TYPE_1__* items; } ;
typedef  TYPE_3__ svn_fs_x__p2l_entry_t ;
struct TYPE_16__ {int /*<<< orphan*/  changes_container_cache; } ;
typedef  TYPE_4__ svn_fs_x__data_t ;
typedef  int /*<<< orphan*/  svn_fs_x__changes_t ;
typedef  int /*<<< orphan*/  svn_fs_x__changes_context_t ;
struct TYPE_17__ {TYPE_4__* fsap_data; } ;
typedef  TYPE_5__ svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_uint32_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_array_header_t ;
struct TYPE_13__ {int /*<<< orphan*/  change_set; } ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  read_item (int /*<<< orphan*/ **,TYPE_5__*,int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_cache__has_key (scalar_t__*,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_cache__set (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__changes_get_list (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__get_revnum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_x__packed_base_rev (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_x__read_changes_container (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
block_read_changes_container(apr_array_header_t **changes,
                             svn_fs_t *fs,
                             svn_fs_x__revision_file_t *rev_file,
                             svn_fs_x__p2l_entry_t* entry,
                             apr_uint32_t sub_item,
                             svn_fs_x__changes_context_t *context,
                             svn_boolean_t must_read,
                             apr_pool_t *result_pool,
                             apr_pool_t *scratch_pool)
{
  svn_fs_x__data_t *ffd = fs->fsap_data;
  svn_fs_x__changes_t *container;
  svn_fs_x__pair_cache_key_t key;
  svn_stream_t *stream;
  svn_revnum_t revision = svn_fs_x__get_revnum(entry->items[0].change_set);

  key.revision = svn_fs_x__packed_base_rev(fs, revision);
  key.second = entry->offset;

  /* already in cache? */
  if (!must_read)
    {
      svn_boolean_t is_cached = FALSE;
      SVN_ERR(svn_cache__has_key(&is_cached, ffd->changes_container_cache,
                                 &key, scratch_pool));
      if (is_cached)
        return SVN_NO_ERROR;
    }

  SVN_ERR(read_item(&stream, fs, rev_file, entry, scratch_pool));

  /* read changes from revision file */

  SVN_ERR(svn_fs_x__read_changes_container(&container, stream, scratch_pool,
                                           scratch_pool));

  /* extract requested data */

  if (must_read)
    SVN_ERR(svn_fs_x__changes_get_list(changes, container, sub_item,
                                       context, result_pool));
  SVN_ERR(svn_cache__set(ffd->changes_container_cache, &key, container,
                         scratch_pool));

  return SVN_NO_ERROR;
}