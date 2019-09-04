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
 int /*<<< orphan*/  dief (char*,...) ; 
 scalar_t__ errno ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 char* strrchr (char const*,char) ; 

__attribute__((used)) static char *dirname(const char *path)
{
    const char *last_slash = strrchr(path, '/');
    char *ret;

    if (last_slash == NULL) {
        errno = 0;
        dief("dirname: no slash in given path:%s", path);
    }
    if ((ret = malloc(last_slash + 1 - path)) == NULL)
        dief("no memory");
    memcpy(ret, path, last_slash - path);
    ret[last_slash - path] = '\0';
    return ret;
}