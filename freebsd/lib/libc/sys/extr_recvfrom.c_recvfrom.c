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
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  socklen_t ;

/* Variables and functions */
 size_t INTERPOS_recvfrom ; 
 scalar_t__* __libc_interposing ; 
 int /*<<< orphan*/  stub1 (int,void*,size_t,int,struct sockaddr*,int /*<<< orphan*/ *) ; 

ssize_t
recvfrom(int s, void *buf, size_t len, int flags,
    struct sockaddr * __restrict from, socklen_t * __restrict fromlen)
{

	return (((ssize_t (*)(int, void *, size_t, int,
	    struct sockaddr *, socklen_t *))
	    __libc_interposing[INTERPOS_recvfrom])(s, buf, len, flags,
	   from, fromlen));
}