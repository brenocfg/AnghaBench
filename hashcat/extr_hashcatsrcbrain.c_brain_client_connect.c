#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
typedef  scalar_t__ u32 ;
struct addrinfo {int /*<<< orphan*/  ai_addrlen; int /*<<< orphan*/  ai_addr; struct addrinfo* ai_next; int /*<<< orphan*/  ai_socktype; int /*<<< orphan*/  ai_family; } ;
typedef  int /*<<< orphan*/  status_ctx_t ;
typedef  int /*<<< orphan*/  response ;
typedef  int /*<<< orphan*/  port_str ;
typedef  int /*<<< orphan*/  passwords_max ;
typedef  int /*<<< orphan*/  password_ok ;
typedef  int /*<<< orphan*/  one ;
typedef  int /*<<< orphan*/  link_speed_t ;
typedef  scalar_t__ i64 ;
typedef  int /*<<< orphan*/  hints ;
struct TYPE_4__ {int brain_link_client_fd; int brain_link_recv_active; int brain_link_send_active; struct addrinfo brain_link_send_speed; struct addrinfo brain_link_recv_speed; scalar_t__ brain_link_send_bytes; scalar_t__ brain_link_recv_bytes; } ;
typedef  TYPE_1__ hc_device_param_t ;
typedef  int /*<<< orphan*/  challenge ;
typedef  int /*<<< orphan*/  brain_session ;
typedef  int /*<<< orphan*/  brain_link_version_ok ;
typedef  int /*<<< orphan*/  brain_link_version ;
typedef  int /*<<< orphan*/  brain_attack ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  BRAIN_CLIENT_CONNECT_TIMEOUT ; 
 scalar_t__ BRAIN_LINK_VERSION_CUR ; 
 int /*<<< orphan*/  SEND_FLAGS ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  SOL_TCP ; 
 int /*<<< orphan*/  TCP_NODELAY ; 
 scalar_t__ brain_auth_hash (scalar_t__,char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ brain_connect (int const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brain_logging (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int brain_recv (int const,scalar_t__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int brain_send (int const,scalar_t__*,int,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  close (int const) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  freeaddrinfo (struct addrinfo*) ; 
 int /*<<< orphan*/  gai_strerror (int const) ; 
 int getaddrinfo (char const*,char*,struct addrinfo*,struct addrinfo**) ; 
 int /*<<< orphan*/  memset (struct addrinfo*,int /*<<< orphan*/ ,int) ; 
 int setsockopt (int const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int const*,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int const) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

bool brain_client_connect (hc_device_param_t *device_param, const status_ctx_t *status_ctx, const char *host, const int port, const char *password, u32 brain_session, u32 brain_attack, i64 passwords_max, u64 *highest)
{
  device_param->brain_link_client_fd   = 0;
  device_param->brain_link_recv_bytes  = 0;
  device_param->brain_link_send_bytes  = 0;
  device_param->brain_link_recv_active = false;
  device_param->brain_link_send_active = false;

  memset (&device_param->brain_link_recv_speed, 0, sizeof (link_speed_t));
  memset (&device_param->brain_link_send_speed, 0, sizeof (link_speed_t));

  const int brain_link_client_fd = socket (AF_INET, SOCK_STREAM, 0);

  if (brain_link_client_fd == -1)
  {
    brain_logging (stderr, 0, "socket: %s\n", strerror (errno));

    return false;
  }

  #if defined (__linux__)
  const int one = 1;

  if (setsockopt (brain_link_client_fd, SOL_TCP, TCP_NODELAY, &one, sizeof (one)) == -1)
  {
    brain_logging (stderr, 0, "setsockopt: %s\n", strerror (errno));

    close (brain_link_client_fd);

    return false;
  }
  #else

  #endif

  struct addrinfo hints;

  memset (&hints, 0, sizeof (hints));

  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;

  char port_str[8];

  snprintf (port_str, sizeof (port_str), "%i", port);

  const char *host_real = (host == NULL) ? "127.0.0.1" : (const char *) host;

  bool connected = false;

  struct addrinfo *address_info;

  const int rc_getaddrinfo = getaddrinfo (host_real, port_str, &hints, &address_info);

  if (rc_getaddrinfo == 0)
  {
    struct addrinfo *address_info_ptr;

    for (address_info_ptr = address_info; address_info_ptr != NULL; address_info_ptr = address_info_ptr->ai_next)
    {
      if (brain_connect (brain_link_client_fd, address_info_ptr->ai_addr, address_info_ptr->ai_addrlen, BRAIN_CLIENT_CONNECT_TIMEOUT) == 0)
      {
        connected = true;

        break;
      }
    }

    freeaddrinfo (address_info);
  }
  else
  {
    brain_logging (stderr, 0, "%s: %s\n", host_real, gai_strerror (rc_getaddrinfo));

    close (brain_link_client_fd);

    return false;
  }

  if (connected == false)
  {
    close (brain_link_client_fd);

    return false;
  }

  device_param->brain_link_client_fd = brain_link_client_fd;

  u32 brain_link_version = BRAIN_LINK_VERSION_CUR;

  if (brain_send (brain_link_client_fd, &brain_link_version, sizeof (brain_link_version), 0, NULL, NULL) == false)
  {
    brain_logging (stderr, 0, "brain_send: %s\n", strerror (errno));

    close (brain_link_client_fd);

    return false;
  }

  u32 brain_link_version_ok;

  if (brain_recv (brain_link_client_fd, &brain_link_version_ok, sizeof (brain_link_version_ok), 0, NULL, NULL) == false)
  {
    brain_logging (stderr, 0, "brain_recv: %s\n", strerror (errno));

    close (brain_link_client_fd);

    return false;
  }

  if (brain_link_version_ok == 0)
  {
    brain_logging (stderr, 0, "Invalid brain server version\n");

    close (brain_link_client_fd);

    return false;
  }

  u32 challenge;

  if (brain_recv (brain_link_client_fd, &challenge, sizeof (challenge), 0, NULL, NULL) == false)
  {
    brain_logging (stderr, 0, "brain_recv: %s\n", strerror (errno));

    close (brain_link_client_fd);

    return false;
  }

  u64 response = brain_auth_hash (challenge, password, strlen (password));

  if (brain_send (brain_link_client_fd, &response, sizeof (response), 0, NULL, NULL) == false)
  {
    brain_logging (stderr, 0, "brain_send: %s\n", strerror (errno));

    close (brain_link_client_fd);

    return false;
  }

  u32 password_ok;

  if (brain_recv (brain_link_client_fd, &password_ok, sizeof (password_ok), 0, NULL, NULL) == false)
  {
    brain_logging (stderr, 0, "brain_recv: %s\n", strerror (errno));

    close (brain_link_client_fd);

    return false;
  }

  if (password_ok == 0)
  {
    brain_logging (stderr, 0, "Invalid brain server password\n");

    close (brain_link_client_fd);

    return false;
  }

  if (brain_send (brain_link_client_fd, &brain_session, sizeof (brain_session), SEND_FLAGS, device_param, status_ctx) == false)
  {
    brain_logging (stderr, 0, "brain_send: %s\n", strerror (errno));

    close (brain_link_client_fd);

    return false;
  }

  if (brain_send (brain_link_client_fd, &brain_attack, sizeof (brain_attack), SEND_FLAGS, device_param, status_ctx) == false)
  {
    brain_logging (stderr, 0, "brain_send: %s\n", strerror (errno));

    close (brain_link_client_fd);

    return false;
  }

  if (brain_send (brain_link_client_fd, &passwords_max, sizeof (passwords_max), SEND_FLAGS, device_param, status_ctx) == false)
  {
    brain_logging (stderr, 0, "brain_send: %s\n", strerror (errno));

    close (brain_link_client_fd);

    return false;
  }

  if (brain_recv (brain_link_client_fd, highest, sizeof (u64), 0, NULL, NULL) == false)
  {
    brain_logging (stderr, 0, "brain_recv: %s\n", strerror (errno));

    close (brain_link_client_fd);

    return false;
  }

  return true;
}