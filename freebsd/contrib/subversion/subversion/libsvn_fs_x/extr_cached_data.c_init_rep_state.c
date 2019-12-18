#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_fs_x__revision_file_t ;
struct TYPE_14__ {scalar_t__ header_size; } ;
typedef  TYPE_2__ svn_fs_x__rep_header_t ;
struct TYPE_15__ {scalar_t__ type; int item_count; scalar_t__ size; scalar_t__ offset; TYPE_1__* items; } ;
typedef  TYPE_3__ svn_fs_x__p2l_entry_t ;
struct TYPE_16__ {int /*<<< orphan*/  combined_window_cache; int /*<<< orphan*/  txdelta_window_cache; } ;
typedef  TYPE_4__ svn_fs_x__data_t ;
struct TYPE_17__ {TYPE_4__* fsap_data; } ;
typedef  TYPE_5__ svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_18__ {int /*<<< orphan*/ * pool; int /*<<< orphan*/  revision; TYPE_5__* fs; int /*<<< orphan*/ * rfile; } ;
typedef  TYPE_6__ shared_file_t ;
struct TYPE_13__ {int /*<<< orphan*/  change_set; } ;
struct TYPE_19__ {int current; int ver; int /*<<< orphan*/  combined_cache; int /*<<< orphan*/  window_cache; scalar_t__ chunk_index; scalar_t__ size; scalar_t__ header_size; scalar_t__ start; TYPE_1__ rep_id; TYPE_6__* sfile; } ;
typedef  TYPE_7__ rep_state_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR_ASSERT (int) ; 
 scalar_t__ SVN_FS_X__ITEM_TYPE_DIR_PROPS ; 
 scalar_t__ SVN_FS_X__ITEM_TYPE_FILE_REP ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 TYPE_6__* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  svn_fs_x__get_revnum (int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
init_rep_state(rep_state_t *rs,
               svn_fs_x__rep_header_t *rep_header,
               svn_fs_t *fs,
               svn_fs_x__revision_file_t *rev_file,
               svn_fs_x__p2l_entry_t* entry,
               apr_pool_t *result_pool)
{
  svn_fs_x__data_t *ffd = fs->fsap_data;
  shared_file_t *shared_file = apr_pcalloc(result_pool, sizeof(*shared_file));

  /* this function does not apply to representation containers */
  SVN_ERR_ASSERT(entry->type >= SVN_FS_X__ITEM_TYPE_FILE_REP
                 && entry->type <= SVN_FS_X__ITEM_TYPE_DIR_PROPS);
  SVN_ERR_ASSERT(entry->item_count == 1);

  shared_file->rfile = rev_file;
  shared_file->fs = fs;
  shared_file->revision = svn_fs_x__get_revnum(entry->items[0].change_set);
  shared_file->pool = result_pool;

  rs->sfile = shared_file;
  rs->rep_id = entry->items[0];
  rs->header_size = rep_header->header_size;
  rs->start = entry->offset + rs->header_size;
  rs->current = 4;
  rs->size = entry->size - rep_header->header_size - 7;
  rs->ver = 1;
  rs->chunk_index = 0;
  rs->window_cache = ffd->txdelta_window_cache;
  rs->combined_cache = ffd->combined_window_cache;

  return SVN_NO_ERROR;
}