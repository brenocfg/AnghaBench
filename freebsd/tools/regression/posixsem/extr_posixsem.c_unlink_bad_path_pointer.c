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
 int /*<<< orphan*/  EFAULT ; 
 int /*<<< orphan*/  ksem_unlink_should_fail (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
unlink_bad_path_pointer(void)
{

	ksem_unlink_should_fail((char *)1024, EFAULT);
}