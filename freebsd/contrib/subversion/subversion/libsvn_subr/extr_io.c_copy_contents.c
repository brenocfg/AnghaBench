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
typedef  int /*<<< orphan*/  buf ;
typedef  scalar_t__ apr_status_t ;
typedef  int apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_file_t ;

/* Variables and functions */
 scalar_t__ APR_STATUS_IS_EOF (scalar_t__) ; 
 scalar_t__ APR_SUCCESS ; 
 int SVN__STREAM_CHUNK_SIZE ; 
 scalar_t__ apr_file_read (int /*<<< orphan*/ *,char*,int*) ; 
 scalar_t__ apr_file_write_full (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static apr_status_t
copy_contents(apr_file_t *from_file,
              apr_file_t *to_file,
              apr_pool_t *pool)
{
  /* Copy bytes till the cows come home. */
  while (1)
    {
      char buf[SVN__STREAM_CHUNK_SIZE];
      apr_size_t bytes_this_time = sizeof(buf);
      apr_status_t read_err;
      apr_status_t write_err;

      /* Read 'em. */
      read_err = apr_file_read(from_file, buf, &bytes_this_time);
      if (read_err && !APR_STATUS_IS_EOF(read_err))
        {
          return read_err;
        }

      /* Write 'em. */
      write_err = apr_file_write_full(to_file, buf, bytes_this_time, NULL);
      if (write_err)
        {
          return write_err;
        }

      if (read_err && APR_STATUS_IS_EOF(read_err))
        {
          /* Return the results of this close: an error, or success. */
          return APR_SUCCESS;
        }
    }
  /* NOTREACHED */
}