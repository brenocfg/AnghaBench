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
struct TYPE_3__ {scalar_t__ total_bytes; scalar_t__ in_memory_size; scalar_t__ alloc; scalar_t__ collect_bucket; scalar_t__ scratch_pool; scalar_t__ file; int /*<<< orphan*/  result_pool; } ;
typedef  TYPE_1__ svn_ra_serf__request_body_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ apr_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 char* allocate_all (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  serf_bucket_aggregate_append (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ serf_bucket_aggregate_create (scalar_t__) ; 
 scalar_t__ serf_bucket_allocator_create (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  serf_bucket_simple_copy_create (char const*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  serf_free_no_error ; 
 int /*<<< orphan*/  svn_io_file_del_on_pool_cleanup ; 
 int /*<<< orphan*/  svn_io_file_write_full (scalar_t__,char const*,scalar_t__,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  svn_io_open_unique_file3 (scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  svn_pool_clear (scalar_t__) ; 
 scalar_t__ svn_pool_create (int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
request_body_stream_write(void *baton,
                          const char *data,
                          apr_size_t *len)
{
  svn_ra_serf__request_body_t *b = baton;

  if (!b->scratch_pool)
    b->scratch_pool = svn_pool_create(b->result_pool);

  if (b->file)
    {
      SVN_ERR(svn_io_file_write_full(b->file, data, *len, NULL,
                                     b->scratch_pool));
      svn_pool_clear(b->scratch_pool);

      b->total_bytes += *len;
    }
  else if (*len + b->total_bytes > b->in_memory_size)
    {
      SVN_ERR(svn_io_open_unique_file3(&b->file, NULL, NULL,
                                       svn_io_file_del_on_pool_cleanup,
                                       b->result_pool, b->scratch_pool));

      if (b->total_bytes)
        {
          const char *all = allocate_all(b, b->scratch_pool);

          SVN_ERR(svn_io_file_write_full(b->file, all, b->total_bytes,
                                         NULL, b->scratch_pool));
        }

      SVN_ERR(svn_io_file_write_full(b->file, data, *len, NULL,
                                     b->scratch_pool));
      b->total_bytes += *len;
    }
  else
    {
      if (!b->alloc)
        b->alloc = serf_bucket_allocator_create(b->scratch_pool,
                                                serf_free_no_error, NULL);

      if (!b->collect_bucket)
        b->collect_bucket = serf_bucket_aggregate_create(b->alloc);

      serf_bucket_aggregate_append(b->collect_bucket,
                                   serf_bucket_simple_copy_create(data, *len,
                                                                  b->alloc));

      b->total_bytes += *len;
    }

  return SVN_NO_ERROR;
}