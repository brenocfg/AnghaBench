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
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_2__ {int /*<<< orphan*/  fd; } ;
struct test_file {TYPE_1__ tf_u; scalar_t__ tf_isdir; } ;

/* Variables and functions */
 int EINVAL ; 
 int errno ; 
 scalar_t__ lseek (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int
test_seek(void *arg, void *h, uint64_t offset, int whence)
{
	struct test_file *tf = h;

	if (tf->tf_isdir)
		return (EINVAL);
	if (lseek(tf->tf_u.fd, offset, whence) < 0)
		return (errno);
	return (0);
}