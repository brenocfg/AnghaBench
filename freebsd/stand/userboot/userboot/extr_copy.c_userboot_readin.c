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
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  CALLBACK (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  copyin ; 
 scalar_t__ read (int,char*,size_t) ; 

ssize_t
userboot_readin(int fd, vm_offset_t va, size_t len)
{
	ssize_t res, s;
	size_t sz;
	char buf[4096];

	res = 0;
	while (len > 0) {
		sz = len;
		if (sz > sizeof(buf))
			sz = sizeof(buf);
		s = read(fd, buf, sz);
		if (s == 0)
			break;
		if (s < 0)
			return (s);
		CALLBACK(copyin, buf, va, s);
		len -= s;
		res += s;
		va += s;
	}
	return (res);
}