#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  h2o_logconf_t ;
struct TYPE_4__ {int fd; int /*<<< orphan*/ * logconf; } ;
typedef  TYPE_1__ h2o_access_log_filehandle_t ;

/* Variables and functions */
 int h2o_access_log_open_log (char const*) ; 
 int /*<<< orphan*/  h2o_error_printf (char*,char*) ; 
 int /*<<< orphan*/ * h2o_logconf_compile (char const*,int,char*) ; 
 int /*<<< orphan*/  h2o_logconf_dispose (int /*<<< orphan*/ *) ; 
 TYPE_1__* h2o_mem_alloc_shared (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  on_dispose_handle ; 

h2o_access_log_filehandle_t *h2o_access_log_open_handle(const char *path, const char *fmt, int escape)
{
    h2o_logconf_t *logconf;
    int fd;
    h2o_access_log_filehandle_t *fh;
    char errbuf[256];

    /* default to combined log format */
    if (fmt == NULL)
        fmt = "%h %l %u %t \"%r\" %s %b \"%{Referer}i\" \"%{User-agent}i\"";
    if ((logconf = h2o_logconf_compile(fmt, escape, errbuf)) == NULL) {
        h2o_error_printf("%s\n", errbuf);
        return NULL;
    }

    /* open log file */
    if ((fd = h2o_access_log_open_log(path)) == -1) {
        h2o_logconf_dispose(logconf);
        return NULL;
    }

    fh = h2o_mem_alloc_shared(NULL, sizeof(*fh), on_dispose_handle);
    fh->logconf = logconf;
    fh->fd = fd;
    return fh;
}