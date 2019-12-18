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
struct checksum_stream_baton {int /*<<< orphan*/  proxy; int /*<<< orphan*/  write_ctx; scalar_t__ write_checksum; } ;
typedef  scalar_t__ apr_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_checksum_update (int /*<<< orphan*/ ,char const*,scalar_t__) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_stream_write (int /*<<< orphan*/ ,char const*,scalar_t__*) ; 

__attribute__((used)) static svn_error_t *
write_handler_checksum(void *baton, const char *buffer, apr_size_t *len)
{
  struct checksum_stream_baton *btn = baton;

  if (btn->write_checksum && *len > 0)
    SVN_ERR(svn_checksum_update(btn->write_ctx, buffer, *len));

  return svn_error_trace(svn_stream_write(btn->proxy, buffer, len));
}