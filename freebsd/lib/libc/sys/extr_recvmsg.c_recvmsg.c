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
struct msghdr {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 size_t INTERPOS_recvmsg ; 
 scalar_t__* __libc_interposing ; 
 int stub1 (int,struct msghdr*,int) ; 

ssize_t
recvmsg(int s, struct msghdr *msg, int flags)
{

	return (((int (*)(int, struct msghdr *, int))
	    __libc_interposing[INTERPOS_recvmsg])(s, msg, flags));
}