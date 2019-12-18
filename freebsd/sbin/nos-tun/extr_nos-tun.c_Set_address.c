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
struct TYPE_2__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {TYPE_1__ sin_addr; int /*<<< orphan*/  sin_family; } ;
struct sockaddr {int dummy; } ;
struct hostent {int /*<<< orphan*/  h_length; int /*<<< orphan*/  h_addr; int /*<<< orphan*/  h_addrtype; } ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  INADDR_NONE ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (char*,int) ; 
 struct hostent* gethostbyname (char*) ; 
 int /*<<< orphan*/  inet_addr (char*) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static int
Set_address(char *addr, struct sockaddr_in *sin)
{
  struct hostent *hp;

  bzero((char *)sin, sizeof(struct sockaddr));
  sin->sin_family = AF_INET;
  if((sin->sin_addr.s_addr = inet_addr(addr)) == INADDR_NONE) {
    hp = gethostbyname(addr);
    if (!hp) {
      syslog(LOG_ERR,"unknown host %s", addr);
      return 1;
    }
    sin->sin_family = hp->h_addrtype;
    bcopy(hp->h_addr, (caddr_t)&sin->sin_addr, hp->h_length);
  }
  return 0;
}