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
struct log {int /*<<< orphan*/  id; struct log* path; } ;
typedef  struct log gzlog ;

/* Variables and functions */
 int /*<<< orphan*/  LOGID ; 
 int /*<<< orphan*/  free (struct log*) ; 
 int /*<<< orphan*/  log_close (struct log*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

int gzlog_close(gzlog *logd)
{
    struct log *log = logd;

    /* check arguments */
    if (log == NULL || strcmp(log->id, LOGID))
        return -3;

    /* close the log file and release the lock */
    log_close(log);

    /* free structure and return */
    if (log->path != NULL)
        free(log->path);
    strcpy(log->id, "bad");
    free(log);
    return 0;
}