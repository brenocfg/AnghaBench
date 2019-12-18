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
struct sockaddr_nl {int /*<<< orphan*/  nl_family; } ;
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  nladdr ;

/* Variables and functions */
 int /*<<< orphan*/  AF_NETLINK ; 
 int /*<<< orphan*/  NETLINK_ROUTE ; 
 int /*<<< orphan*/  PF_NETLINK ; 
 int /*<<< orphan*/  SOCK_RAW ; 
 scalar_t__ bind (int,struct sockaddr*,int) ; 
 int /*<<< orphan*/  memset (struct sockaddr_nl*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nl_close (int) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nl_open(void)
{
  struct sockaddr_nl nladdr;
  int sd;

  sd = socket(PF_NETLINK, SOCK_RAW, NETLINK_ROUTE);
  if (sd < 0) return -1;
  memset(&nladdr, 0, sizeof(nladdr));
  nladdr.nl_family = AF_NETLINK;
  if (bind(sd, (struct sockaddr*)&nladdr, sizeof(nladdr)) < 0){
    nl_close(sd);
    return -1;
  }
  return sd;
}