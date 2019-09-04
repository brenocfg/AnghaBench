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
struct addrinfo {int /*<<< orphan*/  ai_addrlen; int /*<<< orphan*/  ai_addr; int /*<<< orphan*/  ai_protocol; int /*<<< orphan*/  ai_socktype; int /*<<< orphan*/  ai_family; } ;
typedef  int /*<<< orphan*/  ov ;
struct TYPE_2__ {int /*<<< orphan*/  port; int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_UNSPEC ; 
 int /*<<< orphan*/  FATAL (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SOMAXCONN ; 
 int /*<<< orphan*/  SO_REUSEADDR ; 
 scalar_t__ bind (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  freeaddrinfo (struct addrinfo*) ; 
 int /*<<< orphan*/  gai_strerror (int /*<<< orphan*/ ) ; 
 scalar_t__ getaddrinfo (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct addrinfo*,struct addrinfo**) ; 
 int listen (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct addrinfo*,int /*<<< orphan*/ ,int) ; 
 int setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 TYPE_1__ wsconfig ; 

__attribute__((used)) static void
ws_socket (int *listener)
{
  int ov = 1;
  struct addrinfo hints, *ai;

  /* get a socket and bind it */
  memset (&hints, 0, sizeof hints);
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  /*hints.ai_flags = AI_PASSIVE; */
  if (getaddrinfo (wsconfig.host, wsconfig.port, &hints, &ai) != 0)
    FATAL ("Unable to set server: %s.", gai_strerror (errno));

  /* Create a TCP socket.  */
  *listener = socket (ai->ai_family, ai->ai_socktype, ai->ai_protocol);

  /* Options */
  if (setsockopt (*listener, SOL_SOCKET, SO_REUSEADDR, &ov, sizeof (ov)) == -1)
    FATAL ("Unable to set setsockopt: %s.", strerror (errno));

  /* Bind the socket to the address. */
  if (bind (*listener, ai->ai_addr, ai->ai_addrlen) != 0)
    FATAL ("Unable to set bind: %s.", strerror (errno));
  freeaddrinfo (ai);

  /* Tell the socket to accept connections. */
  if (listen (*listener, SOMAXCONN) == -1)
    FATAL ("Unable to listen: %s.", strerror (errno));
}