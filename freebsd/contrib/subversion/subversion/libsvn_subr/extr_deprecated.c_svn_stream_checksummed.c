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
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct md5_stream_baton {unsigned char const** read_digest; unsigned char const** write_digest; int /*<<< orphan*/  write_checksum; int /*<<< orphan*/  read_checksum; int /*<<< orphan*/  proxy; int /*<<< orphan*/ * pool; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 struct md5_stream_baton* apr_palloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  close_handler_md5 ; 
 int /*<<< orphan*/  read_full_handler_md5 ; 
 int /*<<< orphan*/  read_handler_md5 ; 
 int /*<<< orphan*/  skip_handler_md5 ; 
 int /*<<< orphan*/  svn_checksum_md5 ; 
 int /*<<< orphan*/  svn_stream_checksummed2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_stream_create (struct md5_stream_baton*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_set_close (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_stream_set_read2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_stream_set_skip (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_stream_set_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_handler_md5 ; 

svn_stream_t *
svn_stream_checksummed(svn_stream_t *stream,
                       const unsigned char **read_digest,
                       const unsigned char **write_digest,
                       svn_boolean_t read_all,
                       apr_pool_t *pool)
{
  svn_stream_t *s;
  struct md5_stream_baton *baton;

  if (! read_digest && ! write_digest)
    return stream;

  baton = apr_palloc(pool, sizeof(*baton));
  baton->read_digest = read_digest;
  baton->write_digest = write_digest;
  baton->pool = pool;

  /* Set BATON->proxy to a stream that will fill in BATON->read_checksum
   * and BATON->write_checksum (if we want them) when it is closed. */
  baton->proxy
    = svn_stream_checksummed2(stream,
                              read_digest ? &baton->read_checksum : NULL,
                              write_digest ? &baton->write_checksum : NULL,
                              svn_checksum_md5,
                              read_all, pool);

  /* Create a stream that will forward its read/write/close operations to
   * BATON->proxy and will fill in *READ_DIGEST and *WRITE_DIGEST (if we
   * want them) after it closes BATON->proxy. */
  s = svn_stream_create(baton, pool);
  svn_stream_set_read2(s, read_handler_md5, read_full_handler_md5);
  svn_stream_set_skip(s, skip_handler_md5);
  svn_stream_set_write(s, write_handler_md5);
  svn_stream_set_close(s, close_handler_md5);
  return s;
}