#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  total_bytes; int /*<<< orphan*/  all_data; scalar_t__ file; } ;
typedef  TYPE_1__ svn_ra_serf__request_body_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  serf_bucket_t ;
typedef  int /*<<< orphan*/  serf_bucket_alloc_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  scalar_t__ apr_off_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_SET ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/ * serf_bucket_file_create (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * serf_bucket_simple_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_file_seek (scalar_t__,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
request_body_delegate(serf_bucket_t **body_bkt,
                      void *baton,
                      serf_bucket_alloc_t *alloc,
                      apr_pool_t *request_pool,
                      apr_pool_t *scratch_pool)
{
  svn_ra_serf__request_body_t *b = baton;

  if (b->file)
    {
      apr_off_t offset;

      offset = 0;
      SVN_ERR(svn_io_file_seek(b->file, APR_SET, &offset, scratch_pool));

      *body_bkt = serf_bucket_file_create(b->file, alloc);
    }
  else
    {
      *body_bkt = serf_bucket_simple_create(b->all_data,
                                            b->total_bytes,
                                            NULL, NULL, alloc);
    }

  return SVN_NO_ERROR;
}