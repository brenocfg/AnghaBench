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
struct TYPE_2__ {int st_mode; int st_uid; int st_gid; int /*<<< orphan*/  st_size; } ;
struct test_file {TYPE_1__ tf_stat; } ;

/* Variables and functions */

int
test_stat(void *arg, void *h, int *mode_return, int *uid_return, int *gid_return,
    uint64_t *size_return)
{
	struct test_file *tf = h;

	*mode_return = tf->tf_stat.st_mode;
	*uid_return = tf->tf_stat.st_uid;
	*gid_return = tf->tf_stat.st_gid;
	*size_return = tf->tf_stat.st_size;
	return (0);
}