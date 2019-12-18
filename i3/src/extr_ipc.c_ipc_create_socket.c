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
struct sockaddr_un {int /*<<< orphan*/  sun_path; int /*<<< orphan*/  sun_family; } ;
struct sockaddr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_LOCAL ; 
 int /*<<< orphan*/  DEFAULT_DIR_MODE ; 
 int /*<<< orphan*/  DLOG (char*,char*) ; 
 int /*<<< orphan*/  FD_CLOEXEC ; 
 int /*<<< orphan*/  FREE (char*) ; 
 int /*<<< orphan*/  F_SETFD ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 scalar_t__ bind (int,struct sockaddr*,int) ; 
 char* current_socketpath ; 
 char* dirname (char*) ; 
 int /*<<< orphan*/  fcntl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ listen (int,int) ; 
 int /*<<< orphan*/  memset (struct sockaddr_un*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mkdirp (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  path_exists (char const*) ; 
 int /*<<< orphan*/  perror (char*) ; 
 char* resolve_tilde (char const*) ; 
 int /*<<< orphan*/  set_nonblock (int) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* sstrdup (char*) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  unlink (char*) ; 

int ipc_create_socket(const char *filename) {
    int sockfd;

    FREE(current_socketpath);

    char *resolved = resolve_tilde(filename);
    DLOG("Creating IPC-socket at %s\n", resolved);
    char *copy = sstrdup(resolved);
    const char *dir = dirname(copy);
    if (!path_exists(dir))
        mkdirp(dir, DEFAULT_DIR_MODE);
    free(copy);

    /* Unlink the unix domain socket before */
    unlink(resolved);

    if ((sockfd = socket(AF_LOCAL, SOCK_STREAM, 0)) < 0) {
        perror("socket()");
        free(resolved);
        return -1;
    }

    (void)fcntl(sockfd, F_SETFD, FD_CLOEXEC);

    struct sockaddr_un addr;
    memset(&addr, 0, sizeof(struct sockaddr_un));
    addr.sun_family = AF_LOCAL;
    strncpy(addr.sun_path, resolved, sizeof(addr.sun_path) - 1);
    if (bind(sockfd, (struct sockaddr *)&addr, sizeof(struct sockaddr_un)) < 0) {
        perror("bind()");
        free(resolved);
        return -1;
    }

    set_nonblock(sockfd);

    if (listen(sockfd, 5) < 0) {
        perror("listen()");
        free(resolved);
        return -1;
    }

    current_socketpath = resolved;
    return sockfd;
}