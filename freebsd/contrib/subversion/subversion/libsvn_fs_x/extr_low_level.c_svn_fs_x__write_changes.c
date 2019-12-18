#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_stream_t ;
typedef  int /*<<< orphan*/  svn_fs_x__change_t ;
typedef  int /*<<< orphan*/  svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
struct TYPE_5__ {int nelts; } ;
typedef  TYPE_1__ apr_array_header_t ;
struct TYPE_6__ {int /*<<< orphan*/ * value; } ;

/* Variables and functions */
 TYPE_3__ APR_ARRAY_IDX (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_sort__hash (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_sort__item_t ; 
 int /*<<< orphan*/  svn_sort_compare_items_lexically ; 
 int /*<<< orphan*/  svn_stream_puts (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  write_change_entry (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_fs_x__write_changes(svn_stream_t *stream,
                        svn_fs_t *fs,
                        apr_hash_t *changes,
                        svn_boolean_t terminate_list,
                        apr_pool_t *scratch_pool)
{
  apr_pool_t *iterpool = svn_pool_create(scratch_pool);
  apr_array_header_t *sorted_changed_paths;
  int i;

  /* For the sake of the repository administrator sort the changes so
     that the final file is deterministic and repeatable, however the
     rest of the FSX code doesn't require any particular order here.

     Also, this sorting is only effective in writing all entries with
     a single call as write_final_changed_path_info() does.  For the
     list being written incrementally during transaction, we actually
     *must not* change the order of entries from different calls.
   */
  sorted_changed_paths = svn_sort__hash(changes,
                                        svn_sort_compare_items_lexically,
                                        scratch_pool);

  /* Write all items to disk in the new order. */
  for (i = 0; i < sorted_changed_paths->nelts; ++i)
    {
      svn_fs_x__change_t *change;

      svn_pool_clear(iterpool);
      change = APR_ARRAY_IDX(sorted_changed_paths, i, svn_sort__item_t).value;

      /* Write out the new entry into the final rev-file. */
      SVN_ERR(write_change_entry(stream, change, iterpool));
    }

  if (terminate_list)
    svn_stream_puts(stream, "\n");

  svn_pool_destroy(iterpool);

  return SVN_NO_ERROR;
}