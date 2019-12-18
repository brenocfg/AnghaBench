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
struct in_addr {scalar_t__ s_addr; } ;
struct sockaddr_in {struct in_addr sin_addr; } ;
struct sockaddr {scalar_t__ sa_family; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ INADDR_ANY ; 
 scalar_t__ PRC_IS_REDIRECT (int) ; 

__attribute__((used)) static void
div_ctlinput(int cmd, struct sockaddr *sa, void *vip)
{
        struct in_addr faddr;

	faddr = ((struct sockaddr_in *)sa)->sin_addr;
	if (sa->sa_family != AF_INET || faddr.s_addr == INADDR_ANY)
        	return;
	if (PRC_IS_REDIRECT(cmd))
		return;
}