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
struct filecore_direntry {size_t len; int /*<<< orphan*/  member_0; } ;

/* Variables and functions */

int
main(void)
{
	struct filecore_direntry dirent = { 0 };
	size_t  uio_resid = 0;
	size_t bytelen = (((dirent.len)<(uio_resid))?(dirent.len):(uio_resid));
	return bytelen;
}