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
struct memory_type {int /*<<< orphan*/  mt_sizemask; } ;

/* Variables and functions */

uint64_t
memstat_get_sizemask(const struct memory_type *mtp)
{

	return (mtp->mt_sizemask);
}