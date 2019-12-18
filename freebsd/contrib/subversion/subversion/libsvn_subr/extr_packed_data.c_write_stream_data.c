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
struct TYPE_6__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ svn_stringbuf_t ;
typedef  int /*<<< orphan*/  svn_stream_t ;
typedef  int /*<<< orphan*/  svn_error_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_DELTA_COMPRESSION_LEVEL_DEFAULT ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  svn__compress_zlib (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_stream_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stringbuf_setempty (TYPE_1__*) ; 
 int /*<<< orphan*/  write_stream_uint (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
write_stream_data(svn_stream_t *stream,
                  svn_stringbuf_t *uncompressed,
                  svn_stringbuf_t *compressed)
{
  SVN_ERR(svn__compress_zlib(uncompressed->data, uncompressed->len,
                             compressed,
                             SVN_DELTA_COMPRESSION_LEVEL_DEFAULT));

  SVN_ERR(write_stream_uint(stream, compressed->len));
  SVN_ERR(svn_stream_write(stream, compressed->data, &compressed->len));

  svn_stringbuf_setempty(uncompressed);
  svn_stringbuf_setempty(compressed);

  return SVN_NO_ERROR;
}