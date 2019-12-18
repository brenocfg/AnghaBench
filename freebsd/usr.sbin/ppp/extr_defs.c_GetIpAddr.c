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
struct in_addr {void* s_addr; } ;
struct hostent {scalar_t__ h_addrtype; int /*<<< orphan*/  h_length; int /*<<< orphan*/  h_addr; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 void* INADDR_ANY ; 
 void* INADDR_NONE ; 
 struct hostent* gethostbyname (char const*) ; 
 scalar_t__ inet_aton (char const*,struct in_addr*) ; 
 int /*<<< orphan*/  isalnum (char const) ; 
 int /*<<< orphan*/  memcpy (struct in_addr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcasecmp (char const*,char*) ; 
 int /*<<< orphan*/ * strchr (char*,char const) ; 

struct in_addr
GetIpAddr(const char *cp)
{
  struct in_addr ipaddr;

  if (!strcasecmp(cp, "default"))
    ipaddr.s_addr = INADDR_ANY;
  else if (inet_aton(cp, &ipaddr) == 0) {
    const char *ptr;

    /* Any illegal characters ? */
    for (ptr = cp; *ptr != '\0'; ptr++)
      if (!isalnum(*ptr) && strchr("-.", *ptr) == NULL)
        break;

    if (*ptr == '\0') {
      struct hostent *hp;

      hp = gethostbyname(cp);
      if (hp && hp->h_addrtype == AF_INET)
        memcpy(&ipaddr, hp->h_addr, hp->h_length);
      else
        ipaddr.s_addr = INADDR_NONE;
    } else
      ipaddr.s_addr = INADDR_NONE;
  }

  return ipaddr;
}