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
struct stat {int /*<<< orphan*/  st_mode; } ;
typedef  int /*<<< orphan*/  mode_t ;

/* Variables and functions */
 scalar_t__ EEXIST ; 
 int /*<<< orphan*/  ELOG (char*,char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ ENOENT ; 
 scalar_t__ ENOTDIR ; 
 int /*<<< orphan*/  S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ mkdir (char const*,int /*<<< orphan*/ ) ; 
 char* sstrdup (char const*) ; 
 scalar_t__ stat (char const*,struct stat*) ; 
 int /*<<< orphan*/  strerror (scalar_t__) ; 
 int strlen (char*) ; 
 char* strrchr (char*,char) ; 

int mkdirp(const char *path, mode_t mode) {
    if (mkdir(path, mode) == 0)
        return 0;
    if (errno == EEXIST) {
        struct stat st;
        /* Check that the named file actually is a directory. */
        if (stat(path, &st)) {
            ELOG("stat(%s) failed: %s\n", path, strerror(errno));
            return -1;
        }
        if (!S_ISDIR(st.st_mode)) {
            ELOG("mkdir(%s) failed: %s\n", path, strerror(ENOTDIR));
            return -1;
        }
        return 0;
    } else if (errno != ENOENT) {
        ELOG("mkdir(%s) failed: %s\n", path, strerror(errno));
        return -1;
    }
    char *copy = sstrdup(path);
    /* strip trailing slashes, if any */
    while (copy[strlen(copy) - 1] == '/')
        copy[strlen(copy) - 1] = '\0';

    char *sep = strrchr(copy, '/');
    if (sep == NULL) {
        free(copy);
        return -1;
    }
    *sep = '\0';
    int result = -1;
    if (mkdirp(copy, mode) == 0)
        result = mkdirp(path, mode);
    free(copy);

    return result;
}