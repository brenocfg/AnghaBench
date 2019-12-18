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
struct log {int fd; struct log* path; struct log* end; struct log* id; } ;
typedef  struct log gzlog ;

/* Variables and functions */
 char* LOGID ; 
 int /*<<< orphan*/  free (struct log*) ; 
 scalar_t__ log_open (struct log*) ; 
 void* malloc (size_t) ; 
 int /*<<< orphan*/  strcpy (struct log*,char*) ; 
 size_t strlen (char*) ; 

gzlog *gzlog_open(char *path)
{
    size_t n;
    struct log *log;

    /* check arguments */
    if (path == NULL || *path == 0)
        return NULL;

    /* allocate and initialize log structure */
    log = malloc(sizeof(struct log));
    if (log == NULL)
        return NULL;
    strcpy(log->id, LOGID);
    log->fd = -1;

    /* save path and end of path for name construction */
    n = strlen(path);
    log->path = malloc(n + 9);              /* allow for ".repairs" */
    if (log->path == NULL) {
        free(log);
        return NULL;
    }
    strcpy(log->path, path);
    log->end = log->path + n;

    /* gain exclusive access and verify log file -- may perform a
       recovery operation if needed */
    if (log_open(log)) {
        free(log->path);
        free(log);
        return NULL;
    }

    /* return pointer to log structure */
    return log;
}