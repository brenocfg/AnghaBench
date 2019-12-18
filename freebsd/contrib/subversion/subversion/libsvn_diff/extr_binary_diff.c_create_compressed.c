#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  svn_stream_t ;
typedef  int svn_filesize_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  (* svn_cancel_func_t ) (void*) ;
typedef  int /*<<< orphan*/  buffer ;
typedef  int apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_file_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int SVN__STREAM_CHUNK_SIZE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  svn_io_file_del_on_pool_cleanup ; 
 int /*<<< orphan*/  svn_io_file_size_get (int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_open_uniquely_named (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_stream_compressed (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_from_aprfile2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_read_full (int /*<<< orphan*/ *,char*,int*) ; 
 int /*<<< orphan*/  svn_stream_write (int /*<<< orphan*/ *,char*,int*) ; 

__attribute__((used)) static svn_error_t *
create_compressed(apr_file_t **result,
                  svn_filesize_t *full_size,
                  svn_filesize_t *compressed_size,
                  svn_stream_t *original_stream,
                  svn_cancel_func_t cancel_func,
                  void *cancel_baton,
                  apr_pool_t *result_pool,
                  apr_pool_t *scratch_pool)
{
  svn_stream_t *compressed;
  svn_filesize_t bytes_read = 0;
  apr_size_t rd;

  SVN_ERR(svn_io_open_uniquely_named(result, NULL, NULL, "diffgz",
                                     NULL, svn_io_file_del_on_pool_cleanup,
                                     result_pool, scratch_pool));

  compressed = svn_stream_compressed(
                  svn_stream_from_aprfile2(*result, TRUE, scratch_pool),
                  scratch_pool);

  if (original_stream)
    do
    {
      char buffer[SVN__STREAM_CHUNK_SIZE];
      rd = sizeof(buffer);

      if (cancel_func)
        SVN_ERR(cancel_func(cancel_baton));

      SVN_ERR(svn_stream_read_full(original_stream, buffer, &rd));

      bytes_read += rd;
      SVN_ERR(svn_stream_write(compressed, buffer, &rd));
    }
    while(rd == SVN__STREAM_CHUNK_SIZE);
  else
    {
      apr_size_t zero = 0;
      SVN_ERR(svn_stream_write(compressed, NULL, &zero));
    }

  SVN_ERR(svn_stream_close(compressed)); /* Flush compression */

  *full_size = bytes_read;
  SVN_ERR(svn_io_file_size_get(compressed_size, *result, scratch_pool));

  return SVN_NO_ERROR;
}