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
struct in_addr {int dummy; } ;
struct hostent {scalar_t__ h_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  LogWARN ; 
 struct hostent* gethostbyname (char const*) ; 
 scalar_t__ inet_aton (char const*,struct in_addr*) ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*,char const*) ; 

__attribute__((used)) static int
StrToAddr(const char *str, struct in_addr *addr)
{
  struct hostent *hp;

  if (inet_aton(str, addr))
    return 0;

  hp = gethostbyname(str);
  if (!hp) {
    log_Printf(LogWARN, "StrToAddr: Unknown host %s.\n", str);
    return -1;
  }
  *addr = *((struct in_addr *) hp->h_addr);
  return 0;
}