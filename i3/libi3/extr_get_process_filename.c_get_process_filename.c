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
struct stat {int dummy; } ;
struct passwd {char* pw_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*,char*) ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  getpid () ; 
 struct passwd* getpwuid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getuid () ; 
 int mkdir (char*,int) ; 
 int /*<<< orphan*/ * mkdtemp (char*) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  sasprintf (char**,char*,char const*,...) ; 
 scalar_t__ stat (char*,struct stat*) ; 
 int /*<<< orphan*/  warn (char*,char*) ; 

char *get_process_filename(const char *prefix) {
    /* dir stores the directory path for this and all subsequent calls so that
     * we only create a temporary directory once per i3 instance. */
    static char *dir = NULL;
    if (dir == NULL) {
        /* Check if XDG_RUNTIME_DIR is set. If so, we use XDG_RUNTIME_DIR/i3 */
        if ((dir = getenv("XDG_RUNTIME_DIR"))) {
            char *tmp;
            sasprintf(&tmp, "%s/i3", dir);
            dir = tmp;
            struct stat buf;
            if (stat(dir, &buf) != 0) {
                if (mkdir(dir, 0700) == -1) {
                    warn("Could not mkdir(%s)", dir);
                    errx(EXIT_FAILURE, "Check permissions of $XDG_RUNTIME_DIR = '%s'",
                         getenv("XDG_RUNTIME_DIR"));
                    perror("mkdir()");
                    return NULL;
                }
            }
        } else {
            /* If not, we create a (secure) temp directory using the template
             * /tmp/i3-<user>.XXXXXX */
            struct passwd *pw = getpwuid(getuid());
            const char *username = pw ? pw->pw_name : "unknown";
            sasprintf(&dir, "/tmp/i3-%s.XXXXXX", username);
            /* mkdtemp modifies dir */
            if (mkdtemp(dir) == NULL) {
                perror("mkdtemp()");
                return NULL;
            }
        }
    }
    char *filename;
    sasprintf(&filename, "%s/%s.%d", dir, prefix, getpid());
    return filename;
}