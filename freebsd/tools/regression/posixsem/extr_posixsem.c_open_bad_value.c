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
 int /*<<< orphan*/  O_CREAT ; 
 int /*<<< orphan*/  TEST_PATH ; 
 int /*<<< orphan*/  UINT_MAX ; 
 int /*<<< orphan*/  ksem_open_should_fail (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ksem_unlink (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
open_bad_value(void)
{

	(void)ksem_unlink(TEST_PATH);

	ksem_open_should_fail(TEST_PATH, O_CREAT, 0777, UINT_MAX, EINVAL);
}