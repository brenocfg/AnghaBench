#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ svn_stringbuf_t ;
typedef  scalar_t__ svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_packed__data_root_t ;
typedef  int /*<<< orphan*/  svn_packed__byte_stream_t ;
typedef  int /*<<< orphan*/  svn_fs_x__batch_fsync_t ;
typedef  int /*<<< orphan*/  svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_cancel_func_t ;
typedef  int /*<<< orphan*/  apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_file_t ;
typedef  int /*<<< orphan*/  apr_array_header_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_W (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  apr_psprintf (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 int /*<<< orphan*/  svn_dirent_join (char const*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__batch_fsync_open_file (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* svn_fs_x__path_revprops (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_packed__add_bytes (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_packed__create_bytes_stream (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_packed__data_create_root (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stringbuf_from_file2 (TYPE_1__**,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  verify_checksum (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_packed_data_checksummed (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
copy_revprops(svn_fs_t *fs,
              const char *pack_file_dir,
              const char *pack_filename,
              const char *shard_path,
              svn_revnum_t start_rev,
              svn_revnum_t end_rev,
              apr_array_header_t *sizes,
              apr_size_t total_size,
              int compression_level,
              svn_fs_x__batch_fsync_t *batch,
              svn_cancel_func_t cancel_func,
              void *cancel_baton,
              apr_pool_t *scratch_pool)
{
  apr_file_t *pack_file;
  svn_revnum_t rev;
  apr_pool_t *iterpool = svn_pool_create(scratch_pool);

  svn_packed__data_root_t *root = svn_packed__data_create_root(scratch_pool);
  svn_packed__byte_stream_t *stream
    = svn_packed__create_bytes_stream(root);

  /* Iterate over the revisions in this shard, squashing them together. */
  for (rev = start_rev; rev <= end_rev; rev++)
    {
      const char *path;
      svn_stringbuf_t *props;

      svn_pool_clear(iterpool);

      /* Construct the file name. */
      path = svn_fs_x__path_revprops(fs, rev, iterpool);

      /* Copy all the bits from the non-packed revprop file to the end of
       * the pack file. */
      SVN_ERR(svn_stringbuf_from_file2(&props, path, iterpool));
      SVN_ERR_W(verify_checksum(props, iterpool),
                apr_psprintf(iterpool, "Failed to read revprops for r%ld.",
                             rev));

      svn_packed__add_bytes(stream, props->data, props->len);
    }

  /* Create the auto-fsync'ing pack file. */
  SVN_ERR(svn_fs_x__batch_fsync_open_file(&pack_file, batch,
                                          svn_dirent_join(pack_file_dir,
                                                          pack_filename,
                                                          scratch_pool),
                                          scratch_pool));

  /* write all to disk */
  SVN_ERR(write_packed_data_checksummed(root, pack_file, scratch_pool));

  svn_pool_destroy(iterpool);

  return SVN_NO_ERROR;
}