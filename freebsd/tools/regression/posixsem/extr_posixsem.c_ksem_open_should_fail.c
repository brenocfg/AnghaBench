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
typedef  int /*<<< orphan*/  semid_t ;
typedef  int /*<<< orphan*/  mode_t ;

/* Variables and functions */
 int errno ; 
 int /*<<< orphan*/  fail_err (char*) ; 
 int /*<<< orphan*/  fail_errno (char*) ; 
 int /*<<< orphan*/  ksem_close (int /*<<< orphan*/ ) ; 
 scalar_t__ ksem_open (int /*<<< orphan*/ *,char const*,int,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  pass () ; 

__attribute__((used)) static void
ksem_open_should_fail(const char *path, int flags, mode_t mode, unsigned int
    value, int error)
{
	semid_t id;

	if (ksem_open(&id, path, flags, mode, value) >= 0) {
		fail_err("ksem_open() didn't fail");
		ksem_close(id);
		return;
	}
	if (errno != error) {
		fail_errno("ksem_open");
		return;
	}
	pass();
}