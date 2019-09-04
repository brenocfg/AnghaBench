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
 int /*<<< orphan*/  GIT_OBJECT_DIR_MODE ; 
 int /*<<< orphan*/  GIT_OBJECT_FILE_MODE ; 
 int /*<<< orphan*/  test_write_object_permission (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void test_odb_loose__permissions_standard(void)
{
	test_write_object_permission(0, 0, GIT_OBJECT_DIR_MODE, GIT_OBJECT_FILE_MODE);
}