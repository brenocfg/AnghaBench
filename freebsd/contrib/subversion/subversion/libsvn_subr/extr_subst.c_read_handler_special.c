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
struct special_stream_baton {int /*<<< orphan*/  pool; int /*<<< orphan*/  path; scalar_t__ read_stream; } ;
typedef  int /*<<< orphan*/  apr_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_ENOENT ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  svn_dirent_local_style (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_stream_read_full (scalar_t__,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
read_handler_special(void *baton, char *buffer, apr_size_t *len)
{
  struct special_stream_baton *btn = baton;

  if (btn->read_stream)
    /* We actually found a file to read from */
    return svn_stream_read_full(btn->read_stream, buffer, len);
  else
    return svn_error_createf(APR_ENOENT, NULL,
                             _("Can't read special file: File '%s' not found"),
                             svn_dirent_local_style(btn->path, btn->pool));
}