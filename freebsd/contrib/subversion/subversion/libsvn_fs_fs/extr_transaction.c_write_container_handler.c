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
typedef  int /*<<< orphan*/  svn_error_t ;
struct write_container_baton {int /*<<< orphan*/  size; int /*<<< orphan*/  stream; scalar_t__ sha1_ctx; scalar_t__ md5_ctx; } ;
typedef  int /*<<< orphan*/  apr_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  svn_checksum_update (scalar_t__,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_stream_write (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
write_container_handler(void *baton,
                        const char *data,
                        apr_size_t *len)
{
  struct write_container_baton *whb = baton;

  SVN_ERR(svn_checksum_update(whb->md5_ctx, data, *len));
  if (whb->sha1_ctx)
    SVN_ERR(svn_checksum_update(whb->sha1_ctx, data, *len));

  SVN_ERR(svn_stream_write(whb->stream, data, len));
  whb->size += *len;

  return SVN_NO_ERROR;
}