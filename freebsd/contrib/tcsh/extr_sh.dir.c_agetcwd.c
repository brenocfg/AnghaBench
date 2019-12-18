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
typedef  int /*<<< orphan*/  Char ;

/* Variables and functions */
 int ERANGE ; 
 size_t MAXPATHLEN ; 
 int /*<<< orphan*/ * SAVE (char*) ; 
 int errno ; 
 int /*<<< orphan*/ * getcwd (char*,size_t) ; 
 int /*<<< orphan*/  xfree (char*) ; 
 char* xmalloc (size_t) ; 
 char* xrealloc (char*,size_t) ; 

__attribute__((used)) static Char *
agetcwd(void)
{
    char *buf;
    Char *cwd;
    size_t len;

    len = MAXPATHLEN;
    buf = xmalloc(len);
    while (getcwd(buf, len) == NULL) {
	int err;

	err = errno;
	if (err != ERANGE) {
	    xfree(buf);
	    errno = err;
	    return NULL;
	}
	len *= 2;
	buf = xrealloc(buf, len);
    }
    if (*buf == '\0') {
	xfree(buf);
	return NULL;
    }
    cwd = SAVE(buf);
    xfree(buf);
    return cwd;
}