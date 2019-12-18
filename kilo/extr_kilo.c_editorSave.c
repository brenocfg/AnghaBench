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
struct TYPE_2__ {scalar_t__ dirty; int /*<<< orphan*/  filename; } ;

/* Variables and functions */
 TYPE_1__ E ; 
 int O_CREAT ; 
 int O_RDWR ; 
 int /*<<< orphan*/  close (int) ; 
 char* editorRowsToString (int*) ; 
 int /*<<< orphan*/  editorSetStatusMessage (char*,int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (char*) ; 
 int ftruncate (int,int) ; 
 int open (int /*<<< orphan*/ ,int,int) ; 
 int strerror (int /*<<< orphan*/ ) ; 
 int write (int,char*,int) ; 

int editorSave(void) {
    int len;
    char *buf = editorRowsToString(&len);
    int fd = open(E.filename,O_RDWR|O_CREAT,0644);
    if (fd == -1) goto writeerr;

    /* Use truncate + a single write(2) call in order to make saving
     * a bit safer, under the limits of what we can do in a small editor. */
    if (ftruncate(fd,len) == -1) goto writeerr;
    if (write(fd,buf,len) != len) goto writeerr;

    close(fd);
    free(buf);
    E.dirty = 0;
    editorSetStatusMessage("%d bytes written on disk", len);
    return 0;

writeerr:
    free(buf);
    if (fd != -1) close(fd);
    editorSetStatusMessage("Can't save! I/O error: %s",strerror(errno));
    return 1;
}