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
struct stat {scalar_t__ st_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  errorfilename ; 
 int /*<<< orphan*/  rmdir (int /*<<< orphan*/ ) ; 
 int stat (int /*<<< orphan*/ ,struct stat*) ; 
 char* strrchr (int /*<<< orphan*/ ,char) ; 
 int unlink (int /*<<< orphan*/ ) ; 

void purge_zerobyte_logfile(void) {
    struct stat st;
    char *slash;

    if (!errorfilename)
        return;

    /* don't delete the log file if it contains something */
    if ((stat(errorfilename, &st)) == -1 || st.st_size > 0)
        return;

    if (unlink(errorfilename) == -1)
        return;

    if ((slash = strrchr(errorfilename, '/')) != NULL) {
        *slash = '\0';
        /* possibly fails with ENOTEMPTY if there are files (or
         * sockets) left. */
        rmdir(errorfilename);
    }
}