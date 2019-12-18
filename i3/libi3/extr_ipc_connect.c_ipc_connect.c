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
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  FD_CLOEXEC ; 
 int /*<<< orphan*/  F_SETFD ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 scalar_t__ connect (int,struct sockaddr const*,int) ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  fcntl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  memset (struct sockaddr_un*,int /*<<< orphan*/ ,int) ; 
 char* root_atom_contents (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* sstrdup (char const*) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char*,int) ; 

int ipc_connect(const char *socket_path) {
    char *path = NULL;
    if (socket_path != NULL) {
        path = sstrdup(socket_path);
    }

    if (path == NULL) {
        if ((path = getenv("I3SOCK")) != NULL) {
            path = sstrdup(path);
        }
    }

    if (path == NULL) {
        path = root_atom_contents("I3_SOCKET_PATH", NULL, 0);
    }

    if (path == NULL) {
        path = sstrdup("/tmp/i3-ipc.sock");
    }

    int sockfd = socket(AF_LOCAL, SOCK_STREAM, 0);
    if (sockfd == -1)
        err(EXIT_FAILURE, "Could not create socket");

    (void)fcntl(sockfd, F_SETFD, FD_CLOEXEC);

    struct sockaddr_un addr;
    memset(&addr, 0, sizeof(struct sockaddr_un));
    addr.sun_family = AF_LOCAL;
    strncpy(addr.sun_path, path, sizeof(addr.sun_path) - 1);
    if (connect(sockfd, (const struct sockaddr *)&addr, sizeof(struct sockaddr_un)) < 0)
        err(EXIT_FAILURE, "Could not connect to i3 on socket %s", path);
    free(path);
    return sockfd;
}