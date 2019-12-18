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
 size_t INTERPOS_connect ; 
 scalar_t__* __libc_interposing ; 
 int stub1 (int,struct sockaddr const*,int /*<<< orphan*/ ) ; 

int
connect(int s, const struct sockaddr *addr, socklen_t addrlen)
{

	return (((int (*)(int, const struct sockaddr *, socklen_t))
	    __libc_interposing[INTERPOS_connect])(s, addr, addrlen));
}