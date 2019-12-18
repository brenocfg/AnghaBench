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
typedef  int ssize_t ;

/* Variables and functions */
 int MAXPATHLEN ; 
 int errno ; 
 int readlink (char const*,char*,size_t) ; 
 int /*<<< orphan*/  xfree (char*) ; 
 char* xmalloc (size_t) ; 
 char* xrealloc (char*,int) ; 

char *
areadlink(const char *path)
{
    char *buf;
    size_t size;
    ssize_t res;

    size = MAXPATHLEN + 1;
    buf = xmalloc(size);
    while ((size_t)(res = readlink(path, buf, size)) == size) {
	size *= 2;
	buf = xrealloc(buf, size);
    }
    if (res == -1) {
	int err;

	err = errno;
	xfree(buf);
	errno = err;
	return NULL;
    }
    buf[res] = '\0';
    return xrealloc(buf, res + 1);
}