#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  zl_sync; } ;
typedef  TYPE_1__ zilog_t ;
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */

void
zil_set_sync(zilog_t *zilog, uint64_t sync)
{
	zilog->zl_sync = sync;
}