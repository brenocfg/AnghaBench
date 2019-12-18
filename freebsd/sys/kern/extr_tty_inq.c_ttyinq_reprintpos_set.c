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
struct ttyinq {int /*<<< orphan*/  ti_lastblock; int /*<<< orphan*/  ti_reprintblock; int /*<<< orphan*/  ti_end; int /*<<< orphan*/  ti_reprint; } ;

/* Variables and functions */

void
ttyinq_reprintpos_set(struct ttyinq *ti)
{

	ti->ti_reprint = ti->ti_end;
	ti->ti_reprintblock = ti->ti_lastblock;
}