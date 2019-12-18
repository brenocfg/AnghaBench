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
 int /*<<< orphan*/  ELOG (char*,char const*) ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  parse_long (char const*,long*,int) ; 

__attribute__((used)) static int parse_restart_fd(void) {
    const char *restart_fd = getenv("_I3_RESTART_FD");
    if (restart_fd == NULL) {
        return -1;
    }

    long int fd = -1;
    if (!parse_long(restart_fd, &fd, 10)) {
        ELOG("Malformed _I3_RESTART_FD \"%s\"\n", restart_fd);
        return -1;
    }
    return fd;
}