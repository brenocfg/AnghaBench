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
 scalar_t__ ERANGE ; 
 int /*<<< orphan*/  X_OK ; 
 int /*<<< orphan*/  _CS_PATH ; 
 scalar_t__ access (char*,int /*<<< orphan*/ ) ; 
 size_t confstr (int /*<<< orphan*/ ,char*,size_t) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  free (char*) ; 
 char* getcwd (char*,size_t) ; 
 char* getenv (char*) ; 
 int readlink (char const*,char*,size_t) ; 
 int /*<<< orphan*/  sasprintf (char**,char*,char const*,...) ; 
 char* smalloc (size_t) ; 
 char* srealloc (char*,size_t) ; 
 char* sstrdup (char const*) ; 
 int /*<<< orphan*/ * strchr (char const*,char) ; 
 char* strtok (char*,char*) ; 

char *get_exe_path(const char *argv0) {
    size_t destpath_size = 1024;
    size_t tmp_size = 1024;
    char *destpath = smalloc(destpath_size);
    char *tmp = smalloc(tmp_size);

#if defined(__linux__) || defined(__FreeBSD__) || defined(__FreeBSD_kernel__)
/* Linux and Debian/kFreeBSD provide /proc/self/exe */
#if defined(__linux__) || defined(__FreeBSD_kernel__)
    const char *exepath = "/proc/self/exe";
#elif defined(__FreeBSD__)
    const char *exepath = "/proc/curproc/file";
#endif
    ssize_t linksize;

    while ((linksize = readlink(exepath, destpath, destpath_size)) == (ssize_t)destpath_size) {
        destpath_size = destpath_size * 2;
        destpath = srealloc(destpath, destpath_size);
    }
    if (linksize != -1) {
        /* readlink() does not NULL-terminate strings, so we have to. */
        destpath[linksize] = '\0';
        free(tmp);
        return destpath;
    }
#endif

    /* argv[0] is most likely a full path if it starts with a slash. */
    if (argv0[0] == '/') {
        free(tmp);
        free(destpath);
        return sstrdup(argv0);
    }

    /* if argv[0] contains a /, prepend the working directory */
    if (strchr(argv0, '/') != NULL) {
        char *retgcwd;
        while ((retgcwd = getcwd(tmp, tmp_size)) == NULL && errno == ERANGE) {
            tmp_size = tmp_size * 2;
            tmp = srealloc(tmp, tmp_size);
        }
        if (retgcwd != NULL) {
            free(destpath);
            sasprintf(&destpath, "%s/%s", tmp, argv0);
            free(tmp);
            return destpath;
        }
    }

    /* Fall back to searching $PATH (or _CS_PATH in absence of $PATH). */
    char *path = getenv("PATH");
    if (path == NULL) {
        /* _CS_PATH is typically something like "/bin:/usr/bin" */
        while (confstr(_CS_PATH, tmp, tmp_size) > tmp_size) {
            tmp_size = tmp_size * 2;
            tmp = srealloc(tmp, tmp_size);
        }
        sasprintf(&path, ":%s", tmp);
    } else {
        path = sstrdup(path);
    }
    const char *component;
    char *str = path;
    while (1) {
        if ((component = strtok(str, ":")) == NULL)
            break;
        str = NULL;
        free(destpath);
        sasprintf(&destpath, "%s/%s", component, argv0);
        /* Of course this is not 100% equivalent to actually exec()ing the
		 * binary, but meh. */
        if (access(destpath, X_OK) == 0) {
            free(path);
            free(tmp);
            return destpath;
        }
    }
    free(destpath);
    free(path);
    free(tmp);

    /* Last resort: maybe it’s in /usr/bin? */
    return sstrdup("/usr/bin/i3-nagbar");
}