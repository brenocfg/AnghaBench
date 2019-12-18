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
struct memory_type {TYPE_1__* mt_percpu_alloc; } ;
struct TYPE_2__ {int /*<<< orphan*/  mtp_numfrees; } ;

/* Variables and functions */

uint64_t
memstat_get_percpu_numfrees(const struct memory_type *mtp, int cpu)
{

	return (mtp->mt_percpu_alloc[cpu].mtp_numfrees);
}