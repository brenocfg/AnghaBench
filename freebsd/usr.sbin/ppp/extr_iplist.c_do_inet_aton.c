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

/* Variables and functions */
 int /*<<< orphan*/  LogWARN ; 
 int inet_aton (char*,struct in_addr*) ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*,int,char const*) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,int) ; 

__attribute__((used)) static int
do_inet_aton(const char *start, const char *end, struct in_addr *ip)
{
  char ipstr[16];

  if (end - start > 15) {
    log_Printf(LogWARN, "%.*s: Invalid IP address\n", (int)(end-start), start);
    return 0;
  }
  strncpy(ipstr, start, end-start);
  ipstr[end-start] = '\0';
  return inet_aton(ipstr, ip);
}