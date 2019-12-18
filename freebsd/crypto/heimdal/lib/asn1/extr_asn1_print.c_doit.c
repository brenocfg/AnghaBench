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
struct stat {size_t st_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  close (int) ; 
 unsigned char* emalloc (size_t) ; 
 int /*<<< orphan*/  err (int,char*,char const*) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  free (unsigned char*) ; 
 scalar_t__ fstat (int,struct stat*) ; 
 int loop (unsigned char*,size_t,int /*<<< orphan*/ ) ; 
 int open (char const*,int /*<<< orphan*/ ) ; 
 size_t read (int,unsigned char*,size_t) ; 

__attribute__((used)) static int
doit (const char *filename)
{
    int fd = open (filename, O_RDONLY);
    struct stat sb;
    unsigned char *buf;
    size_t len;
    int ret;

    if(fd < 0)
	err (1, "opening %s for read", filename);
    if (fstat (fd, &sb) < 0)
	err (1, "stat %s", filename);
    len = sb.st_size;
    buf = emalloc (len);
    if (read (fd, buf, len) != len)
	errx (1, "read failed");
    close (fd);
    ret = loop (buf, len, 0);
    free (buf);
    return ret;
}