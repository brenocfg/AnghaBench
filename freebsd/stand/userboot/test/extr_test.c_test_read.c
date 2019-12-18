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
struct TYPE_2__ {int /*<<< orphan*/  fd; } ;
struct test_file {TYPE_1__ tf_u; scalar_t__ tf_isdir; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 size_t read (int /*<<< orphan*/ ,void*,size_t) ; 

int
test_read(void *arg, void *h, void *dst, size_t size, size_t *resid_return)
{
	struct test_file *tf = h;
	ssize_t sz;

	if (tf->tf_isdir)
		return (EINVAL);
	sz = read(tf->tf_u.fd, dst, size);
	if (sz < 0)
		return (EINVAL);
	*resid_return = size - sz;
	return (0);
}