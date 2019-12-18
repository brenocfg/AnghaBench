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
typedef  int /*<<< orphan*/  u_short ;
struct servent {int /*<<< orphan*/  s_port; } ;

/* Variables and functions */
 int /*<<< orphan*/  LogWARN ; 
 struct servent* getservbyname (char const*,char const*) ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*,char const*,char const*) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strtol (char const*,char**,int) ; 

__attribute__((used)) static int
StrToPort(const char *str, u_short *port, const char *proto)
{
  struct servent *sp;
  char *end;

  *port = strtol(str, &end, 10);
  if (*end != '\0') {
    sp = getservbyname(str, proto);
    if (sp == NULL) {
      log_Printf(LogWARN, "StrToAddr: Unknown port or service %s/%s.\n",
	        str, proto);
      return -1;
    }
    *port = ntohs(sp->s_port);
  }

  return 0;
}