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
typedef  int /*<<< orphan*/  svn_stream_mark_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct checksum_stream_baton {int /*<<< orphan*/  proxy; scalar_t__ write_ctx; scalar_t__ read_ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_STREAM_SEEK_NOT_SUPPORTED ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  svn_checksum_ctx_reset (scalar_t__) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_reset (int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
seek_handler_checksum(void *baton, const svn_stream_mark_t *mark)
{
  struct checksum_stream_baton *btn = baton;

  /* Only reset support. */
  if (mark)
    {
      return svn_error_create(SVN_ERR_STREAM_SEEK_NOT_SUPPORTED,
                              NULL, NULL);
    }
  else
    {
      if (btn->read_ctx)
        svn_checksum_ctx_reset(btn->read_ctx);

      if (btn->write_ctx)
        svn_checksum_ctx_reset(btn->write_ctx);

      SVN_ERR(svn_stream_reset(btn->proxy));
    }

  return SVN_NO_ERROR;
}