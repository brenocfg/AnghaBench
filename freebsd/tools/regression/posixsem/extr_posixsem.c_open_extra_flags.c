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
 int /*<<< orphan*/  EINVAL ; 
 int O_DIRECT ; 
 int O_RDONLY ; 
 int /*<<< orphan*/  TEST_PATH ; 
 int /*<<< orphan*/  ksem_open_should_fail (int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
open_extra_flags(void)
{

	ksem_open_should_fail(TEST_PATH, O_RDONLY | O_DIRECT, 0777, 1, EINVAL);
}