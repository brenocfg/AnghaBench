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

/* Variables and functions */
 int CTL_HW ; 
 int /*<<< orphan*/  FD_CLOEXEC ; 
 int /*<<< orphan*/  F_SETFD ; 
 int HW_MEMSIZE ; 
 int /*<<< orphan*/  _SC_PAGESIZE ; 
 int /*<<< orphan*/  _SC_PHYS_PAGES ; 
 int /*<<< orphan*/  atexit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close_logbuffer () ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  errorfile ; 
 char* errorfilename ; 
 scalar_t__ fcntl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 char* get_process_filename (char*) ; 
 int /*<<< orphan*/ * logbuffer ; 
 int /*<<< orphan*/  open_logbuffer () ; 
 long long physical_mem_bytes ; 
 int /*<<< orphan*/  purge_zerobyte_logfile ; 
 scalar_t__ shmlog_size ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 long long sysconf (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sysctl (int*,int,long long*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void init_logging(void) {
    if (!errorfilename) {
        if (!(errorfilename = get_process_filename("errorlog")))
            fprintf(stderr, "Could not initialize errorlog\n");
        else {
            errorfile = fopen(errorfilename, "w");
            if (!errorfile) {
                fprintf(stderr, "Could not initialize errorlog on %s: %s\n",
                        errorfilename, strerror(errno));
            } else {
                if (fcntl(fileno(errorfile), F_SETFD, FD_CLOEXEC)) {
                    fprintf(stderr, "Could not set close-on-exec flag\n");
                }
            }
        }
    }
    if (physical_mem_bytes == 0) {
#if defined(__APPLE__)
        int mib[2] = {CTL_HW, HW_MEMSIZE};
        size_t length = sizeof(long long);
        sysctl(mib, 2, &physical_mem_bytes, &length, NULL, 0);
#else
        physical_mem_bytes = (long long)sysconf(_SC_PHYS_PAGES) *
                             sysconf(_SC_PAGESIZE);
#endif
    }
    /* Start SHM logging if shmlog_size is > 0. shmlog_size is SHMLOG_SIZE by
     * default on development versions, and 0 on release versions. If it is
     * not > 0, the user has turned it off, so let's close the logbuffer. */
    if (shmlog_size > 0 && logbuffer == NULL)
        open_logbuffer();
    else if (shmlog_size <= 0 && logbuffer)
        close_logbuffer();
    atexit(purge_zerobyte_logfile);
}