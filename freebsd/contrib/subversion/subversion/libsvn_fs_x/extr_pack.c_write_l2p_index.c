#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_3__ {int /*<<< orphan*/  proto_l2p_index; int /*<<< orphan*/  reps; int /*<<< orphan*/  fs; int /*<<< orphan*/  dir_props; int /*<<< orphan*/  file_props; int /*<<< orphan*/  changes; } ;
typedef  TYPE_1__ pack_context_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_off_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_END ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  append_entries (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_x__l2p_index_from_p2l_entries (char const**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_append_file (char const*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_file_flush (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_file_name_get (char const**,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_file_seek (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_remove_file2 (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
write_l2p_index(pack_context_t *context,
                apr_pool_t *pool)
{
  apr_pool_t *scratch_pool = svn_pool_create(pool);
  const char *temp_name;
  const char *proto_index;
  apr_off_t offset = 0;

  /* lump all items into one bucket.  As target, use the bucket that
   * probably has the most entries already. */
  append_entries(context->reps, context->changes);
  append_entries(context->reps, context->file_props);
  append_entries(context->reps, context->dir_props);

  /* Let the index code do the expensive L2P -> P2L transformation. */
  SVN_ERR(svn_fs_x__l2p_index_from_p2l_entries(&temp_name,
                                               context->fs,
                                               context->reps,
                                               pool, scratch_pool));

  /* Append newly written segment to exisiting proto index file. */
  SVN_ERR(svn_io_file_name_get(&proto_index, context->proto_l2p_index,
                               scratch_pool));

  SVN_ERR(svn_io_file_flush(context->proto_l2p_index, scratch_pool));
  SVN_ERR(svn_io_append_file(temp_name, proto_index, scratch_pool));
  SVN_ERR(svn_io_remove_file2(temp_name, FALSE, scratch_pool));
  SVN_ERR(svn_io_file_seek(context->proto_l2p_index, APR_END, &offset,
                           scratch_pool));

  /* Done. */
  svn_pool_destroy(scratch_pool);

  return SVN_NO_ERROR;
}