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
struct TYPE_2__ {int /*<<< orphan*/  pool; int /*<<< orphan*/  progress_baton; int /*<<< orphan*/  (* progress_func ) (scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ svn_ra_serf__session_t ;
typedef  scalar_t__ apr_off_t ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
svn_ra_serf__progress(void *progress_baton, apr_off_t bytes_read,
                      apr_off_t bytes_written)
{
  const svn_ra_serf__session_t *serf_sess = progress_baton;
  if (serf_sess->progress_func)
    {
      serf_sess->progress_func(bytes_read + bytes_written, -1,
                               serf_sess->progress_baton,
                               serf_sess->pool);
    }
}