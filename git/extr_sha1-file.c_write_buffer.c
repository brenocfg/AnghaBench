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

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int error_errno (int /*<<< orphan*/ ) ; 
 scalar_t__ write_in_full (int,void const*,size_t) ; 

__attribute__((used)) static int write_buffer(int fd, const void *buf, size_t len)
{
	if (write_in_full(fd, buf, len) < 0)
		return error_errno(_("file write error"));
	return 0;
}