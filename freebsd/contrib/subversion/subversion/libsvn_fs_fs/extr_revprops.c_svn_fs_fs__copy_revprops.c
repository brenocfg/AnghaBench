#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ svn_stringbuf_t ;
typedef  int /*<<< orphan*/  svn_stream_t ;
typedef  scalar_t__ svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_cancel_func_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_file_t ;
struct TYPE_10__ {int /*<<< orphan*/  nelts; } ;
typedef  TYPE_2__ apr_array_header_t ;

/* Variables and functions */
 int APR_CREATE ; 
 int /*<<< orphan*/  APR_OS_DEFAULT ; 
 int APR_READ ; 
 int APR_WRITE ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 char const* apr_psprintf (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 int /*<<< orphan*/  serialize_revprops_header (int /*<<< orphan*/ *,scalar_t__,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn__compress_zlib (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 char const* svn_dirent_join (char const*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_file_close (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_file_flush_to_disk (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_file_open (int /*<<< orphan*/ **,char const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_file_write_full (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_copy3 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_stream_from_aprfile2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_stream_from_stringbuf (TYPE_1__*,int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_stringbuf_create_empty (int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_stringbuf_create_ensure (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_fs_fs__copy_revprops(const char *pack_file_dir,
                         const char *pack_filename,
                         const char *shard_path,
                         svn_revnum_t start_rev,
                         svn_revnum_t end_rev,
                         apr_array_header_t *sizes,
                         apr_size_t total_size,
                         int compression_level,
                         svn_boolean_t flush_to_disk,
                         svn_cancel_func_t cancel_func,
                         void *cancel_baton,
                         apr_pool_t *scratch_pool)
{
  svn_stream_t *pack_stream;
  apr_file_t *pack_file;
  svn_revnum_t rev;
  apr_pool_t *iterpool = svn_pool_create(scratch_pool);

  /* create empty data buffer and a write stream on top of it */
  svn_stringbuf_t *uncompressed
    = svn_stringbuf_create_ensure(total_size, scratch_pool);
  svn_stringbuf_t *compressed
    = svn_stringbuf_create_empty(scratch_pool);
  pack_stream = svn_stream_from_stringbuf(uncompressed, scratch_pool);

  /* write the pack file header */
  SVN_ERR(serialize_revprops_header(pack_stream, start_rev, sizes, 0,
                                    sizes->nelts, iterpool));

  /* Some useful paths. */
  SVN_ERR(svn_io_file_open(&pack_file, svn_dirent_join(pack_file_dir,
                                                       pack_filename,
                                                       scratch_pool),
                           APR_WRITE | APR_CREATE, APR_OS_DEFAULT,
                           scratch_pool));

  /* Iterate over the revisions in this shard, squashing them together. */
  for (rev = start_rev; rev <= end_rev; rev++)
    {
      const char *path;
      svn_stream_t *stream;
      apr_file_t *file;

      svn_pool_clear(iterpool);

      /* Construct the file name. */
      path = svn_dirent_join(shard_path, apr_psprintf(iterpool, "%ld", rev),
                             iterpool);

      /* Copy all the bits from the non-packed revprop file to the end of
       * the pack file.  Use unbuffered apr_file_t since we're going to
       * write using 16kb chunks. */
      SVN_ERR(svn_io_file_open(&file, path, APR_READ, APR_OS_DEFAULT,
                               iterpool));
      stream = svn_stream_from_aprfile2(file, FALSE, iterpool);
      SVN_ERR(svn_stream_copy3(stream, pack_stream,
                               cancel_func, cancel_baton, iterpool));
    }

  /* flush stream buffers to content buffer */
  SVN_ERR(svn_stream_close(pack_stream));

  /* compress the content (or just store it for COMPRESSION_LEVEL 0) */
  SVN_ERR(svn__compress_zlib(uncompressed->data, uncompressed->len,
                             compressed, compression_level));

  /* write the pack file content to disk */
  SVN_ERR(svn_io_file_write_full(pack_file, compressed->data, compressed->len,
                                 NULL, scratch_pool));
  if (flush_to_disk)
    SVN_ERR(svn_io_file_flush_to_disk(pack_file, scratch_pool));
  SVN_ERR(svn_io_file_close(pack_file, scratch_pool));

  svn_pool_destroy(iterpool);

  return SVN_NO_ERROR;
}