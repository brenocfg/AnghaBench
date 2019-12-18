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
typedef  int /*<<< orphan*/  yajl_gen ;
struct TYPE_2__ {int /*<<< orphan*/ * restart_state_path; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_DIR_MODE ; 
 int /*<<< orphan*/  DLOG (char*,...) ; 
 int /*<<< orphan*/  ELOG (char*,char*,...) ; 
 int /*<<< orphan*/  LC_NUMERIC ; 
 int O_CREAT ; 
 int O_TRUNC ; 
 int O_WRONLY ; 
 int S_IRUSR ; 
 int S_IWUSR ; 
 int /*<<< orphan*/  close (int) ; 
 TYPE_1__ config ; 
 int /*<<< orphan*/  croot ; 
 char* dirname (char*) ; 
 int /*<<< orphan*/  dump_node (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  get_buf ; 
 char* get_process_filename (char*) ; 
 scalar_t__ mkdirp (char*,int /*<<< orphan*/ ) ; 
 int open (char*,int,int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 char* resolve_tilde (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setlocale (int /*<<< orphan*/ ,char*) ; 
 char* sstrdup (char*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int writeall (int,unsigned char const*,size_t) ; 
 int /*<<< orphan*/  y (int /*<<< orphan*/  (*) (char*),...) ; 
 int /*<<< orphan*/  yajl_gen_alloc (int /*<<< orphan*/ *) ; 

__attribute__((used)) static char *store_restart_layout(void) {
    setlocale(LC_NUMERIC, "C");
    yajl_gen gen = yajl_gen_alloc(NULL);

    dump_node(gen, croot, true);

    setlocale(LC_NUMERIC, "");

    const unsigned char *payload;
    size_t length;
    y(get_buf, &payload, &length);

    /* create a temporary file if one hasn't been specified, or just
     * resolve the tildes in the specified path */
    char *filename;
    if (config.restart_state_path == NULL) {
        filename = get_process_filename("restart-state");
        if (!filename)
            return NULL;
    } else {
        filename = resolve_tilde(config.restart_state_path);
    }

    /* create the directory, it could have been cleaned up before restarting or
     * may not exist at all in case it was user-specified. */
    char *filenamecopy = sstrdup(filename);
    char *base = dirname(filenamecopy);
    DLOG("Creating \"%s\" for storing the restart layout\n", base);
    if (mkdirp(base, DEFAULT_DIR_MODE) != 0)
        ELOG("Could not create \"%s\" for storing the restart layout, layout will be lost.\n", base);
    free(filenamecopy);

    int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        perror("open()");
        free(filename);
        return NULL;
    }

    if (writeall(fd, payload, length) == -1) {
        ELOG("Could not write restart layout to \"%s\", layout will be lost: %s\n", filename, strerror(errno));
        free(filename);
        close(fd);
        return NULL;
    }

    close(fd);

    if (length > 0) {
        DLOG("layout: %.*s\n", (int)length, payload);
    }

    y(free);

    return filename;
}