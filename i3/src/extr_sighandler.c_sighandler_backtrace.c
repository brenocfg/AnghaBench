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
typedef  scalar_t__ pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  DLOG (char*) ; 
 int /*<<< orphan*/  ELOG (char*) ; 
 int /*<<< orphan*/  FREE (char*) ; 
 int /*<<< orphan*/  STDERR_FILENO ; 
 int /*<<< orphan*/  STDIN_FILENO ; 
 int /*<<< orphan*/  STDOUT_FILENO ; 
 scalar_t__ WEXITSTATUS (int) ; 
 int /*<<< orphan*/  WIFEXITED (int) ; 
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dup2 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  execvp (char*,char**) ; 
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__ fork () ; 
 char* getenv (char*) ; 
 scalar_t__ getpid () ; 
 scalar_t__ path_exists (char*) ; 
 int pipe (int*) ; 
 int /*<<< orphan*/  sasprintf (char**,char*,char*,...) ; 
 char** start_argv ; 
 int /*<<< orphan*/  waitpid (scalar_t__,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sighandler_backtrace(void) {
    char *tmpdir = getenv("TMPDIR");
    if (tmpdir == NULL)
        tmpdir = "/tmp";

    pid_t pid_parent = getpid();

    char *filename = NULL;
    int suffix = 0;
    /* Find a unique filename for the backtrace (since the PID of i3 stays the
     * same), so that we don’t overwrite earlier backtraces. */
    do {
        FREE(filename);
        sasprintf(&filename, "%s/i3-backtrace.%d.%d.txt", tmpdir, pid_parent, suffix);
        suffix++;
    } while (path_exists(filename));

    pid_t pid_gdb = fork();
    if (pid_gdb < 0) {
        DLOG("Failed to fork for GDB\n");
        return -1;
    } else if (pid_gdb == 0) {
        /* child */
        int stdin_pipe[2],
            stdout_pipe[2];

        if (pipe(stdin_pipe) == -1) {
            ELOG("Failed to init stdin_pipe\n");
            return -1;
        }
        if (pipe(stdout_pipe) == -1) {
            ELOG("Failed to init stdout_pipe\n");
            return -1;
        }

        /* close standard streams in case i3 is started from a terminal; gdb
         * needs to run without controlling terminal for it to work properly in
         * this situation */
        close(STDIN_FILENO);
        close(STDOUT_FILENO);
        close(STDERR_FILENO);

        /* We provide pipe file descriptors for stdin/stdout because gdb < 7.5
         * crashes otherwise, see
         * https://sourceware.org/bugzilla/show_bug.cgi?id=14114 */
        dup2(stdin_pipe[0], STDIN_FILENO);
        dup2(stdout_pipe[1], STDOUT_FILENO);

        char *pid_s, *gdb_log_cmd;
        sasprintf(&pid_s, "%d", pid_parent);
        sasprintf(&gdb_log_cmd, "set logging file %s", filename);

        char *args[] = {
            "gdb",
            start_argv[0],
            "-p",
            pid_s,
            "-batch",
            "-nx",
            "-ex", gdb_log_cmd,
            "-ex", "set logging on",
            "-ex", "bt full",
            "-ex", "quit",
            NULL};
        execvp(args[0], args);
        DLOG("Failed to exec GDB\n");
        exit(1);
    }
    int status = 0;

    waitpid(pid_gdb, &status, 0);

    /* see if the backtrace was successful or not */
    if (!WIFEXITED(status) || WEXITSTATUS(status) != 0) {
        DLOG("GDB did not run properly\n");
        return -1;
    } else if (!path_exists(filename)) {
        DLOG("GDB executed successfully, but no backtrace was generated\n");
        return -1;
    }
    return 1;
}