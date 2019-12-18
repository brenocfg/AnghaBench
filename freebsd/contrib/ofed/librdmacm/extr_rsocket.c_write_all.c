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
typedef  size_t ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 size_t write (int,void const*,size_t) ; 

__attribute__((used)) static void write_all(int fd, const void *msg, size_t len)
{
	// FIXME: if fd is a socket this really needs to handle EINTR and other conditions.
	ssize_t rc = write(fd, msg, len);
	assert(rc == len);
}