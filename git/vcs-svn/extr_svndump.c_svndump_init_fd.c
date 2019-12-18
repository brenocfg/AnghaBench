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
 scalar_t__ buffer_fdinit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int error_errno (char*,int) ; 
 int /*<<< orphan*/  init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input ; 
 int /*<<< orphan*/  xdup (int) ; 

int svndump_init_fd(int in_fd, int back_fd)
{
	if(buffer_fdinit(&input, xdup(in_fd)))
		return error_errno("cannot open fd %d", in_fd);
	init(xdup(back_fd));
	return 0;
}