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
typedef  int /*<<< orphan*/  tr ;
struct threshold_block {unsigned long threshold_limit; int /*<<< orphan*/  cpu; } ;
struct thresh_restart {unsigned long old_limit; struct threshold_block* b; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 unsigned long THRESHOLD_MAX ; 
 scalar_t__ kstrtoul (char const*,int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  memset (struct thresh_restart*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  smp_call_function_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct thresh_restart*,int) ; 
 int /*<<< orphan*/  threshold_restart_bank ; 

__attribute__((used)) static ssize_t
store_threshold_limit(struct threshold_block *b, const char *buf, size_t size)
{
	struct thresh_restart tr;
	unsigned long new;

	if (kstrtoul(buf, 0, &new) < 0)
		return -EINVAL;

	if (new > THRESHOLD_MAX)
		new = THRESHOLD_MAX;
	if (new < 1)
		new = 1;

	memset(&tr, 0, sizeof(tr));
	tr.old_limit = b->threshold_limit;
	b->threshold_limit = new;
	tr.b = b;

	smp_call_function_single(b->cpu, threshold_restart_bank, &tr, 1);

	return size;
}