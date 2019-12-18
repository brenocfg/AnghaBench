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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int u_long ;
typedef  int /*<<< orphan*/  tv ;
typedef  void* time_t ;
struct timeval {int tv_sec; void* tv_usec; } ;
struct stat {int /*<<< orphan*/  st_mode; } ;
struct sockaddr_un {scalar_t__* sun_path; int /*<<< orphan*/  sun_family; } ;
struct TYPE_2__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_port; TYPE_1__ sin_addr; int /*<<< orphan*/  sin_family; } ;
struct sockaddr {int dummy; } ;
struct hostent {scalar_t__ h_addr; } ;
typedef  int /*<<< orphan*/  local ;
typedef  struct sockaddr SOCKADDR ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  AF_LOCAL ; 
 int /*<<< orphan*/  FIONBIO ; 
 int /*<<< orphan*/  F_GETFL ; 
 int /*<<< orphan*/  F_SETFL ; 
 int INVALID_SOCKET ; 
 int /*<<< orphan*/  IPPROTO_TCP ; 
 int O_NONBLOCK ; 
 int /*<<< orphan*/  PF_LOCAL ; 
 scalar_t__ SOCKET_ERROR ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_RCVTIMEO ; 
 size_t SUN_LEN (struct sockaddr_un*) ; 
 int /*<<< orphan*/  S_ISSOCK (int /*<<< orphan*/ ) ; 
 char* USBMUXD_FILE_PATH ; 
 int /*<<< orphan*/  USBMUXD_SOCKET_PORT ; 
 int WSAGetLastError () ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  closesocket (int) ; 
 scalar_t__ connect (int,struct sockaddr*,size_t) ; 
 int fcntl (int,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 struct hostent* gethostbyname (char*) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 scalar_t__ ioctlsocket (int,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  perror (char*) ; 
 scalar_t__ setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ stat (char const*,struct stat*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strncpy (scalar_t__*,char const*,int) ; 

int dl_connect(int recv_timeout) {
  int fd = -1;
#ifdef WIN32
  fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (fd == INVALID_SOCKET) {
    fprintf(stderr, "device_listener: socket function failed with\
        error %d\n", WSAGetLastError());
    return -1;
  }

  struct hostent *host;
  host = gethostbyname("localhost");
  if (host == NULL) {
    fprintf(stderr, "device_listener: gethostbyname function failed with\
        error %d\n", WSAGetLastError());
    closesocket(fd);
    return -2;
  }

  struct sockaddr_in local;
  local.sin_family = AF_INET;
  local.sin_addr.s_addr = *(uint32_t *)host->h_addr;
  local.sin_port = htons(USBMUXD_SOCKET_PORT);

  if (connect(fd, (SOCKADDR *)&local, sizeof(local)) == SOCKET_ERROR) {
    fprintf(stderr, "device_listener: connect function failed with\
        error %d\n", WSAGetLastError());
    closesocket(fd);
    return -2;
  }

  if (recv_timeout < 0) {
    u_long nb = 1;
    if (ioctlsocket(fd, FIONBIO, &nb)) {
      fprintf(stderr, "device_listener: could not set socket to non-blocking");
    }
  }
#else
  const char *filename = USBMUXD_FILE_PATH;
  struct stat fst;
  if (stat(filename, &fst) ||
      !S_ISSOCK(fst.st_mode) ||
      (fd = socket(PF_LOCAL, SOCK_STREAM, 0)) < 0) {
    return -1;
  }

  struct sockaddr_un name;
  name.sun_family = AF_LOCAL;
  strncpy(name.sun_path, filename, sizeof(name.sun_path));
  name.sun_path[sizeof(name.sun_path) - 1] = 0;
  size_t size = SUN_LEN(&name);
  if (connect(fd, (struct sockaddr *)&name, size) < 0) {
    close(fd);
    return -1;
  }

  if (recv_timeout < 0) {
    int opts = fcntl(fd, F_GETFL);
    if (!opts || fcntl(fd, F_SETFL, (opts | O_NONBLOCK)) < 0) {
      perror("Could not set socket to non-blocking");
    }
  }
#endif
  else {
    long millis = (recv_timeout > 0 ? recv_timeout : 5000);
    struct timeval tv;
    tv.tv_sec = (time_t) (millis / 1000);
    tv.tv_usec = (time_t) ((millis - (tv.tv_sec * 1000)) * 1000);
    if (setsockopt(fd, SOL_SOCKET, SO_RCVTIMEO, (char *)&tv,
          sizeof(tv))) {
      perror("Could not set socket receive timeout");
    }
  }
  return fd;
}