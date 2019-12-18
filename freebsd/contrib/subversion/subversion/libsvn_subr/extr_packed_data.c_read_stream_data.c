#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {size_t len; char* data; } ;
typedef  TYPE_1__ svn_stringbuf_t ;
typedef  int /*<<< orphan*/  svn_stream_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ apr_uint64_t ;
typedef  size_t apr_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  read_stream_uint (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  svn__decompress_zlib (char*,size_t,TYPE_1__*,size_t) ; 
 int /*<<< orphan*/  svn_stream_read_full (int /*<<< orphan*/ *,char*,size_t*) ; 
 int /*<<< orphan*/  svn_stringbuf_ensure (TYPE_1__*,size_t) ; 

__attribute__((used)) static svn_error_t *
read_stream_data(svn_stream_t *stream,
                 apr_size_t uncompressed_len,
                 svn_stringbuf_t *uncompressed,
                 svn_stringbuf_t *compressed)
{
  apr_uint64_t len;
  apr_size_t compressed_len;

  SVN_ERR(read_stream_uint(stream, &len));
  compressed_len = (apr_size_t)len;

  svn_stringbuf_ensure(compressed, compressed_len);
  compressed->len = compressed_len;
  SVN_ERR(svn_stream_read_full(stream, compressed->data, &compressed->len));
  compressed->data[compressed_len] = '\0';

  SVN_ERR(svn__decompress_zlib(compressed->data, compressed->len,
                               uncompressed, uncompressed_len));

  return SVN_NO_ERROR;
}