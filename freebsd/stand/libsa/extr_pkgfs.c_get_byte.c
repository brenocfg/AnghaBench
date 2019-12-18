#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int avail_in; int* next_in; } ;
struct package {int* pkg_buf; TYPE_1__ pkg_zs; int /*<<< orphan*/  pkg_fd; } ;
typedef  int /*<<< orphan*/  off_t ;

/* Variables and functions */
 int /*<<< orphan*/  PKG_BUFSIZE ; 
 int read (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
get_byte(struct package *pkg, off_t *op)
{
	int c;

	if (pkg->pkg_zs.avail_in == 0) {
		c = read(pkg->pkg_fd, pkg->pkg_buf, PKG_BUFSIZE);
		if (c <= 0)
			return (-1);
		pkg->pkg_zs.avail_in = c;
		pkg->pkg_zs.next_in = pkg->pkg_buf;
	}

	c = *pkg->pkg_zs.next_in;
	pkg->pkg_zs.next_in++;
	pkg->pkg_zs.avail_in--;
	(*op)++;
	return (c);
}