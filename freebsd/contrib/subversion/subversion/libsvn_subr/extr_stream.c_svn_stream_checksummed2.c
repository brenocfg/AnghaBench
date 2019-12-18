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
typedef  int /*<<< orphan*/  svn_checksum_t ;
typedef  int /*<<< orphan*/  svn_checksum_kind_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct checksum_stream_baton {int /*<<< orphan*/ * pool; int /*<<< orphan*/  read_more; int /*<<< orphan*/ * proxy; int /*<<< orphan*/ ** write_checksum; int /*<<< orphan*/ ** read_checksum; int /*<<< orphan*/ * write_ctx; int /*<<< orphan*/ * read_ctx; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 struct checksum_stream_baton* apr_palloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  close_handler_checksum ; 
 int /*<<< orphan*/  data_available_handler_checksum ; 
 int /*<<< orphan*/  read_full_handler_checksum ; 
 int /*<<< orphan*/  read_handler_checksum ; 
 int /*<<< orphan*/  seek_handler_checksum ; 
 void* svn_checksum_ctx_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_stream_create (struct checksum_stream_baton*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_set_close (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_stream_set_data_available (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_stream_set_read2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_stream_set_seek (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_stream_set_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ svn_stream_supports_reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_handler_checksum ; 

svn_stream_t *
svn_stream_checksummed2(svn_stream_t *stream,
                        svn_checksum_t **read_checksum,
                        svn_checksum_t **write_checksum,
                        svn_checksum_kind_t checksum_kind,
                        svn_boolean_t read_all,
                        apr_pool_t *pool)
{
  svn_stream_t *s;
  struct checksum_stream_baton *baton;

  if (read_checksum == NULL && write_checksum == NULL)
    return stream;

  baton = apr_palloc(pool, sizeof(*baton));
  if (read_checksum)
    baton->read_ctx = svn_checksum_ctx_create(checksum_kind, pool);
  else
    baton->read_ctx = NULL;

  if (write_checksum)
    baton->write_ctx = svn_checksum_ctx_create(checksum_kind, pool);
  else
    baton->write_ctx = NULL;

  baton->read_checksum = read_checksum;
  baton->write_checksum = write_checksum;
  baton->proxy = stream;
  baton->read_more = read_all;
  baton->pool = pool;

  s = svn_stream_create(baton, pool);
  svn_stream_set_read2(s, read_handler_checksum, read_full_handler_checksum);
  svn_stream_set_write(s, write_handler_checksum);
  svn_stream_set_data_available(s, data_available_handler_checksum);
  svn_stream_set_close(s, close_handler_checksum);
  if (svn_stream_supports_reset(stream))
    svn_stream_set_seek(s, seek_handler_checksum);
  return s;
}