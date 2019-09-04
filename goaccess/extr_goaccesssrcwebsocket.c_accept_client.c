#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sockaddr_storage {int /*<<< orphan*/  ss_family; } ;
struct sockaddr {int dummy; } ;
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  raddr ;
struct TYPE_5__ {int listener; int /*<<< orphan*/  remote_ip; } ;
typedef  TYPE_1__ WSClient ;
typedef  int /*<<< orphan*/  GSLList ;

/* Variables and functions */
 int /*<<< orphan*/  FATAL (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INET6_ADDRSTRLEN ; 
 int /*<<< orphan*/  LOG (char*) ; 
 int accept (int,struct sockaddr*,int*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  inet_ntop (int /*<<< orphan*/ ,void const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * list_create (TYPE_1__*) ; 
 int /*<<< orphan*/ * list_insert_prepend (int /*<<< orphan*/ *,TYPE_1__*) ; 
 TYPE_1__* new_wsclient () ; 
 int /*<<< orphan*/  set_nonblocking (int) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 void* ws_get_raddr (struct sockaddr*) ; 

__attribute__((used)) static int
accept_client (int listener, GSLList ** colist)
{
  WSClient *client;
  struct sockaddr_storage raddr;
  int newfd;
  const void *src = NULL;
  socklen_t alen;

  alen = sizeof (raddr);
  if ((newfd = accept (listener, (struct sockaddr *) &raddr, &alen)) == -1)
    FATAL ("Unable to set accept: %s.", strerror (errno));

  if (newfd == -1) {
    LOG (("Unable to accept: %s.", strerror (errno)));
    return newfd;
  }
  src = ws_get_raddr ((struct sockaddr *) &raddr);

  /* malloc a new client */
  client = new_wsclient ();
  client->listener = newfd;
  inet_ntop (raddr.ss_family, src, client->remote_ip, INET6_ADDRSTRLEN);

  /* add up our new client to keep track of */
  if (*colist == NULL)
    *colist = list_create (client);
  else
    *colist = list_insert_prepend (*colist, client);

  /* make the socket non-blocking */
  set_nonblocking (client->listener);

  return newfd;
}