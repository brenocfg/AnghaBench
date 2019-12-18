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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  size_t uint32_t ;
struct ctl_lun {int /*<<< orphan*/ ** pr_keys; } ;

/* Variables and functions */
 size_t CTL_MAX_INIT_PER_PORT ; 

__attribute__((used)) static uint64_t
ctl_get_prkey(struct ctl_lun *lun, uint32_t residx)
{
	uint64_t *t;

	t = lun->pr_keys[residx/CTL_MAX_INIT_PER_PORT];
	if (t == NULL)
		return (0);
	return (t[residx % CTL_MAX_INIT_PER_PORT]);
}