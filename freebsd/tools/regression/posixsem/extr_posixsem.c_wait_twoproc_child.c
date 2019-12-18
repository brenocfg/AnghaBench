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
 int CSTAT (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_PATH ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ ksem_close (int /*<<< orphan*/ ) ; 
 scalar_t__ ksem_open (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ksem_wait (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
wait_twoproc_child(void *arg)
{
	semid_t id;

	if (ksem_open(&id, TEST_PATH, 0, 0, 0) < 0)
		return (CSTAT(1, errno));
	if (ksem_wait(id) < 0)
		return (CSTAT(2, errno));
	if (ksem_close(id) < 0)
		return (CSTAT(3, errno));
	return (CSTAT(0, 0));
}