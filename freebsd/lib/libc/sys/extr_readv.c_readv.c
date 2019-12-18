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
struct iovec {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 size_t INTERPOS_readv ; 
 scalar_t__* __libc_interposing ; 
 int /*<<< orphan*/  stub1 (int,struct iovec const*,int) ; 

ssize_t
readv(int fd, const struct iovec *iov, int iovcnt)
{

	return (((ssize_t (*)(int, const struct iovec *, int))
	    __libc_interposing[INTERPOS_readv])(fd, iov, iovcnt));
}