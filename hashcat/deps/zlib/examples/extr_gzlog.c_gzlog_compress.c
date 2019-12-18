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
typedef  size_t uint ;
struct log {scalar_t__ last; scalar_t__ first; size_t stored; int /*<<< orphan*/  path; int /*<<< orphan*/  end; int /*<<< orphan*/  fd; int /*<<< orphan*/  id; } ;
typedef  struct log gzlog ;

/* Variables and functions */
 int /*<<< orphan*/  BAIL (int) ; 
 int /*<<< orphan*/  COMPRESS_OP ; 
 size_t DICT ; 
 int /*<<< orphan*/  LOGID ; 
 int O_CREAT ; 
 int O_TRUNC ; 
 int O_WRONLY ; 
 size_t PULL2 (unsigned char*) ; 
 int /*<<< orphan*/  SEEK_CUR ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int close (int) ; 
 int /*<<< orphan*/  free (unsigned char*) ; 
 scalar_t__ log_check (struct log*) ; 
 int log_compress (struct log*,unsigned char*,size_t) ; 
 scalar_t__ log_mark (struct log*,int /*<<< orphan*/ ) ; 
 scalar_t__ log_open (struct log*) ; 
 int /*<<< orphan*/  log_touch (struct log*) ; 
 scalar_t__ lseek (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 unsigned char* malloc (size_t) ; 
 int open (int /*<<< orphan*/ ,int,int) ; 
 size_t read (int /*<<< orphan*/ ,...) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ write (int,...) ; 

int gzlog_compress(gzlog *logd)
{
    int fd, ret;
    uint block;
    size_t len, next;
    unsigned char *data, buf[5];
    struct log *log = logd;

    /* check arguments */
    if (log == NULL || strcmp(log->id, LOGID))
        return -3;

    /* see if we lost the lock -- if so get it again and reload the extra
       field information (it probably changed), recover last operation if
       necessary */
    if (log_check(log) && log_open(log))
        return -1;

    /* create space for uncompressed data */
    len = ((size_t)(log->last - log->first) & ~(((size_t)1 << 10) - 1)) +
          log->stored;
    if ((data = malloc(len)) == NULL)
        return -2;

    /* do statement here is just a cheap trick for error handling */
    do {
        /* read in the uncompressed data */
        if (lseek(log->fd, log->first - 1, SEEK_SET) < 0)
            break;
        next = 0;
        while (next < len) {
            if (read(log->fd, buf, 5) != 5)
                break;
            block = PULL2(buf + 1);
            if (next + block > len ||
                read(log->fd, (char *)data + next, block) != block)
                break;
            next += block;
        }
        if (lseek(log->fd, 0, SEEK_CUR) != log->last + 4 + log->stored)
            break;
        log_touch(log);

        /* write the uncompressed data to the .add file */
        strcpy(log->end, ".add");
        fd = open(log->path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd < 0)
            break;
        ret = (size_t)write(fd, data, len) != len;
        if (ret | close(fd))
            break;
        log_touch(log);

        /* write the dictionary for the next compress to the .temp file */
        strcpy(log->end, ".temp");
        fd = open(log->path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd < 0)
            break;
        next = DICT > len ? len : DICT;
        ret = (size_t)write(fd, (char *)data + len - next, next) != next;
        if (ret | close(fd))
            break;
        log_touch(log);

        /* roll back to compressed data, mark the compress in progress */
        log->last = log->first;
        log->stored = 0;
        if (log_mark(log, COMPRESS_OP))
            break;
        BAIL(7);

        /* compress and append the data (clears mark) */
        ret = log_compress(log, data, len);
        free(data);
        return ret;
    } while (0);

    /* broke out of do above on i/o error */
    free(data);
    return -1;
}