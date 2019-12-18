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
typedef  int /*<<< orphan*/  yoml_t ;
struct sockaddr_un {int /*<<< orphan*/  sun_path; int /*<<< orphan*/  sun_family; } ;
struct passwd {int /*<<< orphan*/  pw_gid; int /*<<< orphan*/  pw_uid; } ;
typedef  int pid_t ;
typedef  int /*<<< orphan*/  h2o_configurator_command_t ;

/* Variables and functions */
 int /*<<< orphan*/  AF_UNIX ; 
 int /*<<< orphan*/  FD_CLOEXEC ; 
 int /*<<< orphan*/  F_SETFD ; 
 int /*<<< orphan*/  H2O_SOMAXCONN ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 scalar_t__ bind (int,void*,int) ; 
 scalar_t__ chown (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ fcntl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_configurator_errprintf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,char const*,...) ; 
 int /*<<< orphan*/  h2o_error_printf (char*,char* const,char const*) ; 
 int h2o_spawnp (char* const,char* const*,int*,int /*<<< orphan*/ ) ; 
 scalar_t__ listen (int,int /*<<< orphan*/ ) ; 
 scalar_t__ pipe (int*) ; 
 int snprintf (int /*<<< orphan*/ ,int,char*,char const*) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char const* strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlink (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int create_spawnproc(h2o_configurator_command_t *cmd, yoml_t *node, const char *dirname, char *const *argv,
                            struct sockaddr_un *sa, struct passwd *pw)
{
    int ret, listen_fd = -1, pipe_fds[2] = {-1, -1};

    /* build socket path */
    sa->sun_family = AF_UNIX;
    ret = snprintf(sa->sun_path, sizeof(sa->sun_path), "%s/_", dirname);
    if (ret < 0 || ret >= sizeof(sa->sun_path)) {
        h2o_configurator_errprintf(cmd, node, "unix socket path too long: %s", dirname);
        goto Error;
    }

    /* create socket */
    if ((listen_fd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
        h2o_configurator_errprintf(cmd, node, "socket(2) failed: %s", strerror(errno));
        goto Error;
    }
    if (bind(listen_fd, (void *)sa, sizeof(*sa)) != 0) {
        h2o_configurator_errprintf(cmd, node, "bind(2) failed: %s", strerror(errno));
        goto Error;
    }
    if (listen(listen_fd, H2O_SOMAXCONN) != 0) {
        h2o_configurator_errprintf(cmd, node, "listen(2) failed: %s", strerror(errno));
        goto Error;
    }
    /* change ownership of socket */
    if (pw != NULL && chown(sa->sun_path, pw->pw_uid, pw->pw_gid) != 0) {
        h2o_configurator_errprintf(cmd, node, "chown(2) failed to change ownership of socket:%s:%s", sa->sun_path, strerror(errno));
        goto Error;
    }

    /* create pipe which is used to notify the termination of the server */
    if (pipe(pipe_fds) != 0) {
        h2o_configurator_errprintf(cmd, node, "pipe(2) failed: %s", strerror(errno));
        pipe_fds[0] = -1;
        pipe_fds[1] = -1;
        goto Error;
    }
    if (fcntl(pipe_fds[1], F_SETFD, FD_CLOEXEC) < 0)
        goto Error;

    /* spawn */
    int mapped_fds[] = {listen_fd, 0,   /* listen_fd to 0 */
                        pipe_fds[0], 5, /* pipe_fds[0] to 5 */
                        -1};
    pid_t pid = h2o_spawnp(argv[0], argv, mapped_fds, 0);
    if (pid == -1) {
        h2o_error_printf("[lib/handler/fastcgi.c] failed to launch helper program %s:%s\n", argv[0], strerror(errno));
        goto Error;
    }

    close(listen_fd);
    listen_fd = -1;
    close(pipe_fds[0]);
    pipe_fds[0] = -1;

    return pipe_fds[1];

Error:
    if (pipe_fds[0] != -1)
        close(pipe_fds[0]);
    if (pipe_fds[1])
        close(pipe_fds[1]);
    if (listen_fd != -1)
        close(listen_fd);
    unlink(sa->sun_path);
    return -1;
}