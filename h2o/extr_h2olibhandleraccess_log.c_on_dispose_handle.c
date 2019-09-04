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
struct TYPE_2__ {int /*<<< orphan*/  fd; int /*<<< orphan*/  logconf; } ;
typedef  TYPE_1__ h2o_access_log_filehandle_t ;

/* Variables and functions */
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_logconf_dispose (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void on_dispose_handle(void *_fh)
{
    h2o_access_log_filehandle_t *fh = _fh;

    h2o_logconf_dispose(fh->logconf);
    close(fh->fd);
}