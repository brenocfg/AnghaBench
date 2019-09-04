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
struct st_h2o_access_logger_t {TYPE_1__* fh; } ;
typedef  int /*<<< orphan*/  h2o_req_t ;
typedef  int /*<<< orphan*/  h2o_logger_t ;
struct TYPE_2__ {int /*<<< orphan*/  fd; int /*<<< orphan*/  logconf; } ;
typedef  TYPE_1__ h2o_access_log_filehandle_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 char* h2o_log_request (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t*,char*) ; 
 int /*<<< orphan*/  write (int /*<<< orphan*/ ,char*,size_t) ; 

__attribute__((used)) static void log_access(h2o_logger_t *_self, h2o_req_t *req)
{
    struct st_h2o_access_logger_t *self = (struct st_h2o_access_logger_t *)_self;
    h2o_access_log_filehandle_t *fh = self->fh;
    char *logline, buf[4096];
    size_t len;

    /* stringify */
    len = sizeof(buf);
    logline = h2o_log_request(fh->logconf, req, &len, buf);

    /* emit */
    write(fh->fd, logline, len);

    /* free memory */
    if (logline != buf)
        free(logline);
}