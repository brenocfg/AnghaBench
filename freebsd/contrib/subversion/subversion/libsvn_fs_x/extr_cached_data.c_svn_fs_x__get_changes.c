#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_31__   TYPE_8__ ;
typedef  struct TYPE_30__   TYPE_7__ ;
typedef  struct TYPE_29__   TYPE_6__ ;
typedef  struct TYPE_28__   TYPE_5__ ;
typedef  struct TYPE_27__   TYPE_4__ ;
typedef  struct TYPE_26__   TYPE_3__ ;
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_1__ ;

/* Type definitions */
struct TYPE_24__ {scalar_t__ second; int /*<<< orphan*/  revision; } ;
typedef  TYPE_1__ svn_fs_x__pair_cache_key_t ;
struct TYPE_25__ {int /*<<< orphan*/  number; int /*<<< orphan*/  change_set; } ;
typedef  TYPE_2__ svn_fs_x__id_t ;
struct TYPE_26__ {int /*<<< orphan*/  changes_cache; int /*<<< orphan*/  changes_container_cache; } ;
typedef  TYPE_3__ svn_fs_x__data_t ;
struct TYPE_27__ {scalar_t__ count; scalar_t__ changes; int /*<<< orphan*/  end_offset; int /*<<< orphan*/  eol; } ;
typedef  TYPE_4__ svn_fs_x__changes_list_t ;
struct TYPE_28__ {int start; int /*<<< orphan*/  sub_item; int /*<<< orphan*/ * eol; } ;
typedef  TYPE_5__ svn_fs_x__changes_get_list_baton_t ;
struct TYPE_29__ {TYPE_8__* fs; scalar_t__ next; int /*<<< orphan*/  revision_file; int /*<<< orphan*/  next_offset; int /*<<< orphan*/  eol; int /*<<< orphan*/  revision; } ;
typedef  TYPE_6__ svn_fs_x__changes_context_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  scalar_t__ apr_off_t ;
struct TYPE_30__ {char* elts; scalar_t__ nelts; scalar_t__ nalloc; } ;
typedef  TYPE_7__ apr_array_header_t ;
struct TYPE_31__ {TYPE_3__* fsap_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_FS_X__ITEM_INDEX_CHANGES ; 
 int /*<<< orphan*/  SVN_FS_X__ITEM_TYPE_CHANGES ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 TYPE_7__* apr_array_make (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  block_read (void**,TYPE_8__*,TYPE_2__*,int /*<<< orphan*/ ,TYPE_6__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dbg__log_access (TYPE_8__*,TYPE_2__*,TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_cache__get (void**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_cache__get_partial (void**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__change_set_by_rev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_x__changes_get_list_func ; 
 scalar_t__ svn_fs_x__is_packed_rev (TYPE_8__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_x__item_offset (scalar_t__*,int /*<<< orphan*/ *,TYPE_8__*,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__packed_base_rev (TYPE_8__*,int /*<<< orphan*/ ) ; 

svn_error_t *
svn_fs_x__get_changes(apr_array_header_t **changes,
                      svn_fs_x__changes_context_t *context,
                      apr_pool_t *result_pool,
                      apr_pool_t *scratch_pool)
{
  svn_boolean_t found;
  svn_fs_x__data_t *ffd = context->fs->fsap_data;

  svn_fs_x__id_t id;
  id.change_set = svn_fs_x__change_set_by_rev(context->revision);
  id.number = SVN_FS_X__ITEM_INDEX_CHANGES;

  /* try cache lookup first */

  if (svn_fs_x__is_packed_rev(context->fs, context->revision))
    {
      apr_off_t offset;
      svn_fs_x__pair_cache_key_t key;
      svn_fs_x__changes_get_list_baton_t baton;
      baton.start = (int)context->next;
      baton.eol = &context->eol;

      SVN_ERR(svn_fs_x__item_offset(&offset, &baton.sub_item, context->fs,
                                    context->revision_file,
                                    &id, scratch_pool));
      key.revision = svn_fs_x__packed_base_rev(context->fs,
                                               context->revision);
      key.second = offset;

      SVN_ERR(svn_cache__get_partial((void **)changes, &found,
                                     ffd->changes_container_cache, &key,
                                     svn_fs_x__changes_get_list_func,
                                     &baton, result_pool));
    }
  else
    {
      svn_fs_x__changes_list_t *changes_list;
      svn_fs_x__pair_cache_key_t key;
      key.revision = context->revision;
      key.second = context->next;

      SVN_ERR(svn_cache__get((void **)&changes_list, &found,
                             ffd->changes_cache, &key, result_pool));

      if (found)
        {
          /* Where to look next - if there is more data. */
          context->eol = changes_list->eol;
          context->next_offset = changes_list->end_offset;

          /* Return the block as a "proper" APR array. */
          (*changes) = apr_array_make(result_pool, 0, sizeof(void *));
          (*changes)->elts = (char *)changes_list->changes;
          (*changes)->nelts = changes_list->count;
          (*changes)->nalloc = changes_list->count;
        }
    }

  if (!found)
    {
      /* 'block-read' will also provide us with the desired data */
      SVN_ERR(block_read((void **)changes, context->fs, &id,
                         context->revision_file, context,
                         result_pool, scratch_pool));
    }

  context->next += (*changes)->nelts;

  SVN_ERR(dbg__log_access(context->fs, &id, *changes,
                          SVN_FS_X__ITEM_TYPE_CHANGES, scratch_pool));

  return SVN_NO_ERROR;
}