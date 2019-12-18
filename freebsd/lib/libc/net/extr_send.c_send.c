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
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 size_t INTERPOS_sendto ; 
 scalar_t__* __libc_interposing ; 
 int /*<<< orphan*/  stub1 (int,void const*,size_t,int,struct sockaddr const*,socklen_t) ; 

ssize_t
send(int s, const void *msg, size_t len, int flags)
{
	/*
	 * POSIX says send() shall be a cancellation point, so call the
	 * cancellation-enabled sendto() and not _sendto().
	 */
	return (((ssize_t (*)(int, const void *, size_t, int,
	    const struct sockaddr *, socklen_t))
	    __libc_interposing[INTERPOS_sendto])(s, msg, len, flags,
	    NULL, 0));
}