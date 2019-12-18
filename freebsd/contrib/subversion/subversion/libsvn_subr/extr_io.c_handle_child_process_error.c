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
typedef  int /*<<< orphan*/  errbuf ;
typedef  int /*<<< orphan*/  apr_status_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_file_t ;

/* Variables and functions */
 int /*<<< orphan*/  ERRFILE_KEY ; 
 int /*<<< orphan*/  apr_file_printf (int /*<<< orphan*/ *,char*,char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ apr_pool_userdata_get (void**,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_strerror (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void
handle_child_process_error(apr_pool_t *pool, apr_status_t status,
                           const char *desc)
{
  char errbuf[256];
  apr_file_t *errfile;
  void *p;

  /* We can't do anything if we get an error here, so just return. */
  if (apr_pool_userdata_get(&p, ERRFILE_KEY, pool))
    return;
  errfile = p;

  if (errfile)
    /* What we get from APR is in native encoding. */
    apr_file_printf(errfile, "%s: %s",
                    desc, apr_strerror(status, errbuf,
                                       sizeof(errbuf)));
}