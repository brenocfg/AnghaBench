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
struct tmpfstestargs {int dummy; } ;
typedef  int /*<<< orphan*/  atf_tc_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct tmpfstestargs*) ; 

int
tmpfs_fstest_delfs(const atf_tc_t *tc, void *buf)
{
	struct tmpfstestargs *args = buf;

	free(args);

	return 0;
}