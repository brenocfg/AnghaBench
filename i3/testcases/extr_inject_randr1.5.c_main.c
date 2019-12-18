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
struct sockaddr_un {char* sun_path; int /*<<< orphan*/  sun_family; } ;
struct sockaddr {int dummy; } ;
struct option {char* member_0; char* name; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  const member_1; } ;
struct ev_loop {int dummy; } ;
typedef  int pid_t ;
typedef  int /*<<< orphan*/  ev_io ;
typedef  int /*<<< orphan*/  ev_child ;

/* Variables and functions */
 int /*<<< orphan*/  AF_LOCAL ; 
 int /*<<< orphan*/  AF_UNIX ; 
 int /*<<< orphan*/  EV_READ ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  FD_CLOEXEC ; 
 int /*<<< orphan*/  F_SETFD ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  atexit (int /*<<< orphan*/ ) ; 
 int bind (int,struct sockaddr*,int) ; 
 int /*<<< orphan*/  child_cb ; 
 int /*<<< orphan*/  cleanup_socket ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  ev_child_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ev_child_start (struct ev_loop*,int /*<<< orphan*/ *) ; 
 struct ev_loop* ev_default_loop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ev_io_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ev_io_start (struct ev_loop*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ev_run (struct ev_loop*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  execvp (char*,char**) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 scalar_t__ fcntl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int fork () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  getmonitors_reply ; 
 int getopt_long (int,char**,char*,struct option*,int*) ; 
 int /*<<< orphan*/  getoutputinfo_reply ; 
 int listen (int,int) ; 
 int /*<<< orphan*/  memset (struct sockaddr_un*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  must_read_reply (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  optarg ; 
 int optind ; 
#define  required_argument 128 
 int /*<<< orphan*/  sasprintf (char**,char*,int) ; 
 int /*<<< orphan*/  setenv (char*,char*,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sstrdup (char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  sun_path ; 
 int /*<<< orphan*/  uds_connection_cb ; 
 int /*<<< orphan*/  warn (char*,...) ; 

int main(int argc, char *argv[]) {
    static struct option long_options[] = {
        {"getmonitors_reply", required_argument, 0, 0},
        {"getoutputinfo_reply", required_argument, 0, 0},
        {0, 0, 0, 0},
    };
    char *options_string = "";
    int opt;
    int option_index = 0;

    while ((opt = getopt_long(argc, argv, options_string, long_options, &option_index)) != -1) {
        switch (opt) {
            case 0: {
                const char *option_name = long_options[option_index].name;
                if (strcmp(option_name, "getmonitors_reply") == 0) {
                    must_read_reply(optarg, &getmonitors_reply);
                } else if (strcmp(option_name, "getoutputinfo_reply") == 0) {
                    must_read_reply(optarg, &getoutputinfo_reply);
                }
                break;
            }
            default:
                exit(EXIT_FAILURE);
        }
    }

    if (optind >= argc) {
        errx(EXIT_FAILURE, "syntax: %s [options] <command>", argv[0]);
    }

    int fd = socket(AF_LOCAL, SOCK_STREAM, 0);
    if (fd == -1) {
        err(EXIT_FAILURE, "socket(AF_UNIX)");
    }

    if (fcntl(fd, F_SETFD, FD_CLOEXEC)) {
        warn("Could not set FD_CLOEXEC");
    }

    struct sockaddr_un addr;
    memset(&addr, 0, sizeof(struct sockaddr_un));
    addr.sun_family = AF_UNIX;
    int i;
    bool bound = false;
    for (i = 0; i < 100; i++) {
        /* XXX: The path to X11 sockets differs on some platforms (e.g. Trusted
         * Solaris, HPUX), but since libxcb doesn’t provide a function to
         * generate the path, we’ll just have to hard-code it for now. */
        snprintf(addr.sun_path, sizeof(addr.sun_path), "/tmp/.X11-unix/X%d", i);

        if (bind(fd, (struct sockaddr *)&addr, sizeof(struct sockaddr_un)) == -1) {
            warn("bind(%s)", addr.sun_path);
        } else {
            bound = true;
            /* Let the user know bind() was successful, so that they know the
             * error messages can be disregarded. */
            fprintf(stderr, "Successfuly bound to %s\n", addr.sun_path);
            sun_path = sstrdup(addr.sun_path);
            break;
        }
    }

    if (!bound) {
        err(EXIT_FAILURE, "bind()");
    }

    atexit(cleanup_socket);

    /* This program will be started for each testcase which requires it, so we
     * expect precisely one connection. */
    if (listen(fd, 1) == -1) {
        err(EXIT_FAILURE, "listen()");
    }

    pid_t child = fork();
    if (child == -1) {
        err(EXIT_FAILURE, "fork()");
    }
    if (child == 0) {
        char *display;
        sasprintf(&display, ":%d", i);
        setenv("DISPLAY", display, 1);
        free(display);

        char **child_args = argv + optind;
        execvp(child_args[0], child_args);
        err(EXIT_FAILURE, "exec()");
    }

    struct ev_loop *loop = ev_default_loop(0);

    ev_child cw;
    ev_child_init(&cw, child_cb, child, 0);
    ev_child_start(loop, &cw);

    ev_io watcher;
    ev_io_init(&watcher, uds_connection_cb, fd, EV_READ);
    ev_io_start(loop, &watcher);

    ev_run(loop, 0);
}