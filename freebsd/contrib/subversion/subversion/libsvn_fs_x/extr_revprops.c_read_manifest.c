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
typedef  int /*<<< orphan*/  svn_stringbuf_t ;
typedef  scalar_t__ svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_packed__int_stream_t ;
typedef  int /*<<< orphan*/  svn_packed__data_root_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_3__ {int /*<<< orphan*/  tag; scalar_t__ start_rev; } ;
typedef  TYPE_1__ manifest_entry_t ;
typedef  scalar_t__ apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_array_header_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR_W (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/ * apr_array_make (int /*<<< orphan*/ *,int,int) ; 
 TYPE_1__* apr_array_push (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_psprintf (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 int /*<<< orphan*/  read_packed_data_checksummed (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_packed__first_int_stream (int /*<<< orphan*/ *) ; 
 scalar_t__ svn_packed__get_int (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_packed__get_uint (int /*<<< orphan*/ *) ; 
 scalar_t__ svn_packed__int_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_packed__next_int_stream (int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
read_manifest(apr_array_header_t **manifest,
              svn_stringbuf_t *content,
              svn_revnum_t revision,
              apr_pool_t *result_pool,
              apr_pool_t *scratch_pool)
{
  apr_size_t i;
  apr_size_t count;

  svn_packed__data_root_t *root;
  svn_packed__int_stream_t *start_rev_stream;
  svn_packed__int_stream_t *tag_stream;

  /* Verify the checksum and decode packed data. */
  SVN_ERR_W(read_packed_data_checksummed(&root, content, result_pool,
                                         scratch_pool),
            apr_psprintf(scratch_pool,
                         "Revprop manifest file for r%ld is corrupt",
                         revision));

  /* get streams */
  start_rev_stream = svn_packed__first_int_stream(root);
  tag_stream = svn_packed__next_int_stream(start_rev_stream);

  /* read ids array */
  count = svn_packed__int_count(start_rev_stream);
  *manifest = apr_array_make(result_pool, (int)count,
                            sizeof(manifest_entry_t));

  for (i = 0; i < count; ++i)
    {
      manifest_entry_t *entry = apr_array_push(*manifest);
      entry->start_rev = (svn_revnum_t)svn_packed__get_int(start_rev_stream);
      entry->tag = svn_packed__get_uint(tag_stream);
    }

  return SVN_NO_ERROR;
}