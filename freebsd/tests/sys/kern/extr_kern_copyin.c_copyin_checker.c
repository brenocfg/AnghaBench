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
typedef  int ssize_t ;

/* Variables and functions */
 int errno ; 
 int /*<<< orphan*/  scratch_file ; 
 int write (int /*<<< orphan*/ ,void const*,size_t) ; 

__attribute__((used)) static int
copyin_checker(uintptr_t uaddr, size_t len)
{
	ssize_t ret;

	ret = write(scratch_file, (const void *)uaddr, len);
	return (ret == -1 ? errno : 0);
}