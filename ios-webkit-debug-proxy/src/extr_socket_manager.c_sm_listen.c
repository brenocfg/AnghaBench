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
typedef  int u_long ;
struct TYPE_2__ {void* s_addr; } ;
struct sockaddr_in {void* sin_port; TYPE_1__ sin_addr; void* sin_family; } ;
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  ra ;
typedef  int /*<<< orphan*/  local ;
typedef  struct sockaddr SOCKADDR ;

/* Variables and functions */
 void* AF_INET ; 
 int /*<<< orphan*/  FIONBIO ; 
 int /*<<< orphan*/  F_GETFL ; 
 void* INADDR_ANY ; 
 int INVALID_SOCKET ; 
 int /*<<< orphan*/  IPPROTO_TCP ; 
 scalar_t__ SOCKET_ERROR ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_REUSEADDR ; 
 int WSAGetLastError () ; 
 scalar_t__ bind (int,struct sockaddr*,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  closesocket (int) ; 
 int fcntl (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 void* htons (int) ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ioctlsocket (int,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ listen (int,int) ; 
 scalar_t__ setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int socket (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 

int sm_listen(int port) {
  int fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
#ifdef WIN32
  if (fd == INVALID_SOCKET) {
    fprintf(stderr, "socket_manager: socket function failed with\
        error %d\n", WSAGetLastError());
    return -1;
  }
  struct sockaddr_in local;
  local.sin_family = AF_INET;
  local.sin_addr.s_addr = INADDR_ANY;
  local.sin_port = htons(port);
  int ra = 1;
  u_long nb = 1;
  if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, (char *)&ra,
        sizeof(ra)) == SOCKET_ERROR ||
      ioctlsocket(fd, FIONBIO, &nb) ||
      bind(fd, (SOCKADDR *)&local, sizeof(local)) == SOCKET_ERROR ||
      listen(fd, 5)) {
    fprintf(stderr, "socket_manager: bind failed with\
        error %d\n", WSAGetLastError());
    closesocket(fd);
    return -1;
  }
#else
  if (fd < 0) {
    return -1;
  }
  int opts = fcntl(fd, F_GETFL);
  struct sockaddr_in local;
  local.sin_family = AF_INET;
  local.sin_addr.s_addr = INADDR_ANY;
  local.sin_port = htons(port);
  int ra = 1;
  int nb = 1;
  if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, (char *)&ra,sizeof(ra)) < 0 ||
      opts < 0 ||
      ioctl(fd, FIONBIO, (char *)&nb) < 0 ||
      bind(fd, (struct sockaddr*)&local, sizeof(local)) < 0 ||
      listen(fd, 5)) {
    close(fd);
    return -1;
  }
#endif
  return fd;
}