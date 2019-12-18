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
typedef  scalar_t__ uint32_t ;
struct bps {int /*<<< orphan*/  bytes; } ;

/* Variables and functions */

void
do_bps(const char *desc, struct bps *bps, uint32_t len)
{
	bps->bytes += len;
}