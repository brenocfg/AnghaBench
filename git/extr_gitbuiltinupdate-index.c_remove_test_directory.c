#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ len; } ;

/* Variables and functions */
 TYPE_1__ mtime_dir ; 
 int /*<<< orphan*/  remove_dir_recursively (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void remove_test_directory(void)
{
	if (mtime_dir.len)
		remove_dir_recursively(&mtime_dir, 0);
}