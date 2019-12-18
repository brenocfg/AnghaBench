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
struct servent {int /*<<< orphan*/  s_port; } ;

/* Variables and functions */
 int /*<<< orphan*/  LogWARN ; 
 struct servent* getservbyname (char const*,char const*) ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*,char const*) ; 
 int ntohs (int /*<<< orphan*/ ) ; 
 int strtol (char const*,char**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ParsePort(const char *service, const char *proto)
{
  struct servent *servent;
  char *cp;
  int port;

  servent = getservbyname(service, proto);
  if (servent != NULL)
    return ntohs(servent->s_port);

  port = strtol(service, &cp, 0);
  if (cp == service) {
    log_Printf(LogWARN, "ParsePort: %s is not a port name or number.\n",
	      service);
    return 0;
  }
  return port;
}