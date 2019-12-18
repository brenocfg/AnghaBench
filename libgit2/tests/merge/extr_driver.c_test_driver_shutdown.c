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
struct test_merge_driver {int shutdown; } ;
typedef  int /*<<< orphan*/  git_merge_driver ;

/* Variables and functions */

__attribute__((used)) static void test_driver_shutdown(git_merge_driver *s)
{
	struct test_merge_driver *self = (struct test_merge_driver *)s;
	self->shutdown = 1;
}