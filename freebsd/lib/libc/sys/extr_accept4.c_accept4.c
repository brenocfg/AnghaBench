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
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  socklen_t ;

/* Variables and functions */
 size_t INTERPOS_accept4 ; 
 scalar_t__* __libc_interposing ; 
 int stub1 (int,struct sockaddr*,int /*<<< orphan*/ *,int) ; 

int
accept4(int s, struct sockaddr *addr, socklen_t *addrlen, int flags)
{

	return (((int (*)(int, struct sockaddr *, socklen_t *, int))
	    __libc_interposing[INTERPOS_accept4])(s, addr, addrlen, flags));
}