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

/* Variables and functions */
 int /*<<< orphan*/  fail_err (char*,int,int) ; 
 int /*<<< orphan*/  fail_errno (char*) ; 
 scalar_t__ ksem_getvalue (int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int
checkvalue(semid_t id, int expected)
{
	int val;

	if (ksem_getvalue(id, &val) < 0) {
		fail_errno("ksem_getvalue");
		return (-1);
	}
	if (val != expected) {
		fail_err("sem value should be %d instead of %d", expected, val);
		return (-1);
	}
	return (0);
}