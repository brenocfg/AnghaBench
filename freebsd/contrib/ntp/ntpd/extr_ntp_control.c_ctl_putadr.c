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
typedef  int /*<<< orphan*/  u_int32 ;
typedef  int /*<<< orphan*/  sockaddr_u ;

/* Variables and functions */
 int /*<<< orphan*/  ctl_putunqstr (char const*,char const*,int /*<<< orphan*/ ) ; 
 char* numtoa (int /*<<< orphan*/ ) ; 
 char* stoa (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static void
ctl_putadr(
	const char *tag,
	u_int32 addr32,
	sockaddr_u *addr
	)
{
	const char *cq;

	if (NULL == addr)
		cq = numtoa(addr32);
	else
		cq = stoa(addr);
	ctl_putunqstr(tag, cq, strlen(cq));
}