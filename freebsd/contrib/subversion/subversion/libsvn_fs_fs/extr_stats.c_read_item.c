#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {size_t len; scalar_t__* data; } ;
typedef  TYPE_1__ svn_stringbuf_t ;
struct TYPE_9__ {int /*<<< orphan*/  file; int /*<<< orphan*/  block_size; } ;
typedef  TYPE_2__ svn_fs_fs__revision_file_t ;
struct TYPE_10__ {size_t size; int /*<<< orphan*/  offset; } ;
typedef  TYPE_3__ svn_fs_fs__p2l_entry_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  svn_io_file_aligned_seek (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_file_read_full2 (int /*<<< orphan*/ ,scalar_t__*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_stringbuf_create_ensure (size_t,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
read_item(svn_stringbuf_t **contents,
          svn_fs_fs__revision_file_t *rev_file,
          svn_fs_fs__p2l_entry_t *entry,
          apr_pool_t *result_pool,
          apr_pool_t *scratch_pool)
{
  svn_stringbuf_t *item = svn_stringbuf_create_ensure(entry->size,
                                                      result_pool);
  item->len = entry->size;
  item->data[item->len] = 0;

  SVN_ERR(svn_io_file_aligned_seek(rev_file->file, rev_file->block_size,
                                   NULL, entry->offset, scratch_pool));
  SVN_ERR(svn_io_file_read_full2(rev_file->file, item->data, item->len,
                                 NULL, NULL, scratch_pool));

  *contents = item;

  return SVN_NO_ERROR;
}