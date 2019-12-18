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
typedef  int /*<<< orphan*/  au_stat_t ;

/* Variables and functions */
 int /*<<< orphan*/  A_GETSTAT ; 
 int /*<<< orphan*/  EINVAL ; 
 int auditon (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  errno ; 

int
audit_set_stat(au_stat_t *stats, size_t sz)
{

	if (sizeof(*stats) != sz) {
		errno = EINVAL;
		return (-1);
	}

	return (auditon(A_GETSTAT, stats, sz));
}