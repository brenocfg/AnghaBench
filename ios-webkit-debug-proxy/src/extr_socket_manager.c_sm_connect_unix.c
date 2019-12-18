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
struct sockaddr_un {int /*<<< orphan*/  sun_path; int /*<<< orphan*/  sun_family; } ;
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  name ;

/* Variables and functions */
 int /*<<< orphan*/  AF_UNIX ; 
 int /*<<< orphan*/  F_GETFL ; 
 int /*<<< orphan*/  F_SETFL ; 
 int O_NONBLOCK ; 
 int /*<<< orphan*/  PF_UNIX ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  S_ISSOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ connect (int,struct sockaddr*,int) ; 
 int /*<<< orphan*/  errno ; 
 int fcntl (int,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,char*) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ stat (char const*,struct stat*) ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char const*,int) ; 

int sm_connect_unix(const char *filename) {
  struct sockaddr_un name;
  int sfd = -1;
  struct stat fst;

  if (stat(filename, &fst) != 0 || !S_ISSOCK(fst.st_mode)) {
    fprintf(stderr, "File '%s' is not a socket: %s\n", filename,
        strerror(errno));
    return -1;
  }

  if ((sfd = socket(PF_UNIX, SOCK_STREAM, 0)) < 0) {
    perror("create socket failed");
    return -1;
  }

  int opts = fcntl(sfd, F_GETFL);
  if (fcntl(sfd, F_SETFL, (opts | O_NONBLOCK)) < 0) {
    perror("failed to set socket to non-blocking");
    return -1;
  }

  name.sun_family = AF_UNIX;
  strncpy(name.sun_path, filename, sizeof(name.sun_path) - 1);

  if (connect(sfd, (struct sockaddr*)&name, sizeof(name)) < 0) {
    close(sfd);
    perror("connect failed");
    return -1;
  }

  return sfd;
}