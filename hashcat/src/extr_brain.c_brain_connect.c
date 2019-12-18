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
struct sockaddr {int dummy; } ;
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  so_error ;
typedef  int /*<<< orphan*/  msg ;

/* Variables and functions */
 int FORMAT_MESSAGE_FROM_SYSTEM ; 
 int FORMAT_MESSAGE_IGNORE_INSERTS ; 
 int /*<<< orphan*/  F_GETFL ; 
 int /*<<< orphan*/  F_SETFL ; 
 int /*<<< orphan*/  FormatMessage (int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LANG_NEUTRAL ; 
 int /*<<< orphan*/  MAKELANGID (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int const O_NONBLOCK ; 
 scalar_t__ SOCKET_ERROR ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_ERROR ; 
 int /*<<< orphan*/  SUBLANG_DEFAULT ; 
 int WSAGetLastError () ; 
 int /*<<< orphan*/  brain_logging (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ connect (int,struct sockaddr const*,int) ; 
 int errno ; 
 int fcntl (int,int /*<<< orphan*/ ,int const) ; 
 int getsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int select_write_timeout (int,int const) ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (int) ; 

int brain_connect (int sockfd, const struct sockaddr *addr, socklen_t addrlen, const int timeout)
{
  #if defined (_WIN)

  if (timeout == 99999999)
  {
    // timeout not support on windows
  }

  if (connect (sockfd, addr, addrlen) == SOCKET_ERROR)
  {
    int err = WSAGetLastError ();

    char msg[256];

    memset (msg, 0, sizeof (msg));

    FormatMessage (FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,   // flags
                   NULL,                // lpsource
                   err,                 // message id
                   MAKELANGID (LANG_NEUTRAL, SUBLANG_DEFAULT),    // languageid
                   msg,                 // output buffer
                   sizeof (msg),        // size of msgbuf, bytes
                   NULL);               // va_list of arguments

    brain_logging (stderr, 0, "connect: %s\n", msg);

    return -1;
  }

  #else

  const int old_mode = fcntl (sockfd, F_GETFL, 0);

  if (fcntl (sockfd, F_SETFL, old_mode | O_NONBLOCK) == -1)
  {
    brain_logging (stderr, 0, "fcntl: %s\n", strerror (errno));

    return -1;
  }

  connect (sockfd, addr, addrlen);

  const int rc_select = select_write_timeout (sockfd, timeout);

  if (rc_select == -1) return -1;

  if (rc_select == 0)
  {
    brain_logging (stderr, 0, "connect: timeout\n");

    return -1;
  }

  int so_error = 0;

  socklen_t len = sizeof (so_error);

  if (getsockopt (sockfd, SOL_SOCKET, SO_ERROR, &so_error, &len) == -1)
  {
    brain_logging (stderr, 0, "getsockopt: %s\n", strerror (errno));

    return -1;
  }

  if (fcntl (sockfd, F_SETFL, old_mode) == -1)
  {
    brain_logging (stderr, 0, "fcntl: %s\n", strerror (errno));

    return -1;
  }

  if (so_error != 0)
  {
    brain_logging (stderr, 0, "connect: %s\n", strerror (so_error));

    return -1;
  }

  #endif

  return 0;
}